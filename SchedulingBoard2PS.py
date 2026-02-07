# rm_PollingServer_scheduler.py
# ------------------------------------------------------------
# RM + Polling Server (PS) "puro" (Buttazzo-style) - VERSIONE JOB-BASED
#
# Questa versione riflette la tua implementazione CMSIS-RTOS2:
# - Il thread PS si "attiva" SOLO al rilascio periodico (k*Ts).
# - All'attivazione, se non ci sono richieste pendenti, non fa lavoro e si riaddormenta.
# - Se ci sono richieste, le serve consumando AL PIÙ Cs ms (budget) e poi termina il job.
# - Se la coda si svuota prima, termina subito (non resta runnable).
# - Se arrivano nuove richieste dopo che il PS ha terminato, aspettano il prossimo rilascio.
#
# Callback aperiodiche dipendenti dallo start dei task periodici:
# - Quando un job periodico di lettura inizia a eseguire (primo ms), schedula callback aperiodiche.
# - Controller: +2ms
# - Gyro: +4ms
# - Sonar: +[2..25]ms oppure triplo Left/Front/Right con delay diversi (parametro).
#
# Plot:
# - Baseline per task (rette).
# - Barre che partono dalla retta.
# - Release: linea verticale nera.
# - Fine job periodici: end-cap (ultimo rettangolino) più evidente (alto e/o colore).
# - Callback: segmento start→Ta disegnato nella corsia del task periodico sorgente.
# - PS: ms colorati in base alla callback servita (sorgente distinta, incl. sonar triplo).
# - Legenda in basso a destra.
# ------------------------------------------------------------

import matplotlib.pyplot as plt
from math import gcd
from functools import reduce
from collections import deque
import random
import argparse
from matplotlib.lines import Line2D
from matplotlib.patches import Patch
from matplotlib.ticker import FuncFormatter

# ============================================================
# CONFIGURAZIONE (Board2)
# ============================================================

# ------------------------------------------------------------
# Risoluzione temporale simulazione/plot
# - La simulazione avanza a quanti di TIME_QUANTUM_US microsecondi.
# - Tutti i tempi di input (C, T, delay, Cs, Ts) sono espressi in microsecondi.
# - TIME_QUANTUM_US deve essere un divisore comune di tutti i tempi usati.
# ------------------------------------------------------------
TIME_QUANTUM_US_CHOICES = (10, 50, 100, 500)
DEFAULT_TIME_QUANTUM_US = 100

# Task periodici (nome, C, T) in microsecondi
tasks = [
    ("ReadController", 200, 20_000),
    ("ReadGyroscope",  200, 40_000),
    ("Supervisor",    15_000, 50_000),
    ("ReadSonar",      2_000, 100_000),
]

# Polling Server (nome, Cs, Ts) in microsecondi
PS = ("PS", 1_000, 10_000)

# -------------------------
# Dinamica Sonar: 1 callback oppure 3 callback (Left/Front/Right)
# -------------------------
SONAR_TRIPLE_CALLBACKS = True   # False => una sola callback "Sonar"

# Callback singole (delay_min, delay_max, C_callback)
SENSOR_CALLBACKS_SINGLE = {
    "ReadController": (2_000, 2_000, 200),
    "ReadGyroscope":  (4_000, 2_000, 200),
    "ReadSonar":      (2_000, 25_000, 600),
}

# Sonar triplo (delay diversi per generare arrivi distinti)
SONAR_CALLBACKS_TRIPLE = {
    "ReadSonarLeft":  (10_000, 10_000, 200),
    "ReadSonarFront": (18_000, 18_000, 200),
    "ReadSonarRight": (25_000, 25_000, 200),
}

# Delay worst-case (max) oppure random nel range (ripetibile con seed)
USE_WORST_CASE_DELAY = True
RANDOM_SEED = 1

# Tie-break Ts == Ttask:
# True  => periodico normale vince su PS (PS sotto)
# False => PS vince a parità
PERIODIC_WINS_TIE = True

# -------------------------
# Fine job periodici: end-cap (senza enfasi di altezza)
# -------------------------
FINISH_CAP_MODE = "normal"        # mantenuto per compatibilità (non usa più altezza extra)
FINISH_CAP_COLOR = "black"        # (non usato: il cap resta del colore del task)
FINISH_CAP_HEIGHT = 0.95          # (non usato)
# ============================================================


# ============================================================
# Utility
# ============================================================

def lcm(a, b):
    return a * b // gcd(a, b)

def hyperperiod(periods):
    return reduce(lcm, periods)

def rm_utilization(periodic_tasks, ps=None):
    U = sum(C / T for _, C, T in periodic_tasks)
    if ps is not None:
        _, Cs, Ts = ps
        U += Cs / Ts
    return U

def liu_layland_bound(n):
    return n * (2 ** (1 / n) - 1)

def ps_bound_P(tasks_periodic, PS_tuple):
    _, Cs, Ts = PS_tuple
    Ui = [C / T for _, C, T in tasks_periodic]
    P = 1.0
    for u in Ui:
        P *= (u + 1.0)
    Us = Cs / Ts
    Us_max = (2.0 - P) / P
    return Ui, P, Us, Us_max


# ============================================================
# Argparse + quantizzazione tempo (tick = TIME_QUANTUM_US)
# ============================================================

def parse_args():
    parser = argparse.ArgumentParser(add_help=True)
    parser.add_argument(
        "--dt-us",
        type=int,
        default=DEFAULT_TIME_QUANTUM_US,
        choices=TIME_QUANTUM_US_CHOICES,
        help="Risoluzione temporale (microsecondi) per simulazione/plot.",
    )
    return parser.parse_args()


args = parse_args()
DT_US = int(args.dt_us)


def _ensure_multiple_of_dt_us(label: str, value_us: int):
    if value_us % DT_US != 0:
        raise ValueError(
            f"{label}={value_us}us non è multiplo di DT_US={DT_US}us. "
            "Scegli un DT_US diverso oppure allinea i tempi di input."
        )


def us_to_ticks(value_us: int) -> int:
    _ensure_multiple_of_dt_us("time", value_us)
    return value_us // DT_US


def ticks_to_us(value_ticks: int) -> int:
    return int(value_ticks) * DT_US


def validate_timebase_configuration():
    # Periodici + PS
    for name, C_us, T_us in tasks:
        _ensure_multiple_of_dt_us(f"{name}.C", C_us)
        _ensure_multiple_of_dt_us(f"{name}.T", T_us)
    ps_name_local, Cs_us, Ts_us = PS
    _ensure_multiple_of_dt_us(f"{ps_name_local}.Cs", Cs_us)
    _ensure_multiple_of_dt_us(f"{ps_name_local}.Ts", Ts_us)

    # Callback / delay
    for k, (dmin_us, dmax_us, Ccb_us) in SENSOR_CALLBACKS_SINGLE.items():
        _ensure_multiple_of_dt_us(f"CB[{k}].dmin", dmin_us)
        _ensure_multiple_of_dt_us(f"CB[{k}].dmax", dmax_us)
        _ensure_multiple_of_dt_us(f"CB[{k}].C", Ccb_us)
    for k, (dmin_us, dmax_us, Ccb_us) in SONAR_CALLBACKS_TRIPLE.items():
        _ensure_multiple_of_dt_us(f"CB[{k}].dmin", dmin_us)
        _ensure_multiple_of_dt_us(f"CB[{k}].dmax", dmax_us)
        _ensure_multiple_of_dt_us(f"CB[{k}].C", Ccb_us)


validate_timebase_configuration()


# ============================================================
# Costruisci la lista "sorgenti callback" (per colori/legenda)
# ============================================================

def callback_sources():
    src = ["ReadController", "ReadGyroscope"]
    if SONAR_TRIPLE_CALLBACKS:
        src += ["ReadSonarLeft", "ReadSonarFront", "ReadSonarRight"]
    else:
        src += ["ReadSonar"]
    return src

CALLBACK_SOURCES = callback_sources()


# ============================================================
# Check dimensionamento server (bound con P) + LL (extra)
# ============================================================

ps_name, Cs, Ts = PS

if Cs <= 0 or Ts <= 0:
    raise ValueError("PS: Cs e Ts devono essere > 0")
if Cs > Ts:
    raise ValueError("PS: deve valere Cs <= Ts (altrimenti Us>1)")

Ui, P, Us, Us_max = ps_bound_P(tasks, PS)

print("\n--- Dimensionamento Polling Server (bound con P) ---")
print("Ui (periodici):", [round(u, 6) for u in Ui])
print(f"P = Π(Ui+1) = {P:.6f}")
print(f"Us = Cs/Ts = {Us:.6f} ({Us*100:.2f}%)")
print(f"Us_max     = {Us_max:.6f} ({Us_max*100:.2f}%)")
if Us_max < 0:
    print("✘ ATTENZIONE: Us_max < 0 -> bound non lascia spazio al server.")
elif Us <= Us_max:
    print("✔ OK: il tuo Polling Server soddisfa Us <= Us_max (condizione sufficiente).")
else:
    print("✘ NO: il tuo Polling Server NON soddisfa Us <= Us_max (nessuna garanzia con questo bound).")

H = hyperperiod([T for _, _, T in tasks] + [Ts])

U_tot = rm_utilization(tasks, PS)
n_ll = len(tasks) + 1
U_ll = liu_layland_bound(n_ll)

print(f"\nRisoluzione simulazione DT = {DT_US} us")
print(f"Iperperiodo H = {H} us ({H/1000.0:.3f} ms)")
print(f"Utilizzazione totale (incl. PS) U = {U_tot:.3f} ({U_tot*100:.1f}%)")
print(f"Limite teorico RM (n={n_ll}) U_ll = {U_ll:.3f} ({U_ll*100:.1f}%)")
print("✔ LL sufficiente: schedulabile" if U_tot <= U_ll else "✘ LL non garantisce schedulabilità")


# ============================================================
# Simulazione RM + Polling Server puro (JOB-BASED) + callback dipendenti
# ============================================================

if not USE_WORST_CASE_DELAY:
    random.seed(RANDOM_SEED)

tasks_ticks = [(name, us_to_ticks(C), us_to_ticks(T)) for name, C, T in tasks]
PS_ticks = (ps_name, us_to_ticks(Cs), us_to_ticks(Ts))

time = 0  # tick
jobs = []             # job periodici attivi: {"id","name","remaining","period","release"} (ticks)
schedule = []         # (t_tick, task_name) ogni DT_US
job_id_counter = 0

release_times = {name: [] for name, _, _ in tasks_ticks}
release_times[ps_name] = []

# coda aperiodici (serviti dal PS)
aper_q = deque()      # {"id","src","remaining","arrival","C"} (ticks)

# eventi futuri callback: (Ta, cb_id, src, C)
future_events = []    # (Ta_tick, cb_id, src, C_ticks)

# per plot: link start→Ta (nella corsia del task periodico sorgente)
cb_links = []         # (src_callback, task_periodico_sorgente, t_start_tick, Ta_tick, C_ticks, cb_id)

# per PS colorato: t -> src_callback
ps_exec_src = {}      # t_tick -> src_callback

# fine job periodici: end-cap all'ultimo ms
finish_caps = []      # (t_last_exec_tick, task_name)

# PS job-based (None o dict con remaining=Cs)
ps_job = None         # remaining in ticks

# tracking start job periodici per generare callback una sola volta per job
started_job_ids = set()

cb_id_counter = 0

def choose_delay(dmin, dmax):
    return dmax if USE_WORST_CASE_DELAY else random.randint(dmin, dmax)

def enqueue_future_event(Ta_tick: int, src_cb: str, Ccb_tick: int, task_src: str, t_start_tick: int):
    """Registra evento futuro + link per plot."""
    global cb_id_counter
    if Ta_tick > H_tick:
        return
    cb_id = cb_id_counter
    cb_id_counter += 1
    future_events.append((Ta_tick, cb_id, src_cb, Ccb_tick))
    cb_links.append((src_cb, task_src, t_start_tick, Ta_tick, Ccb_tick, cb_id))

def schedule_callbacks_from_task(task_name: str, start_time_tick: int):
    """Genera callback quando il task periodico inizia a eseguire."""
    if task_name == "ReadController":
        dmin_us, dmax_us, Ccb_us = SENSOR_CALLBACKS_SINGLE["ReadController"]
        dmin = us_to_ticks(dmin_us)
        dmax = us_to_ticks(dmax_us)
        Ccb = us_to_ticks(Ccb_us)
        Ta = start_time_tick + choose_delay(dmin, dmax)
        enqueue_future_event(Ta, "ReadController", Ccb, "ReadController", start_time_tick)

    elif task_name == "ReadGyroscope":
        dmin_us, dmax_us, Ccb_us = SENSOR_CALLBACKS_SINGLE["ReadGyroscope"]
        dmin = us_to_ticks(dmin_us)
        dmax = us_to_ticks(dmax_us)
        Ccb = us_to_ticks(Ccb_us)
        Ta = start_time_tick + choose_delay(dmin, dmax)
        enqueue_future_event(Ta, "ReadGyroscope", Ccb, "ReadGyroscope", start_time_tick)

    elif task_name == "ReadSonar":
        if SONAR_TRIPLE_CALLBACKS:
            for cb_name, (dmin_us, dmax_us, Ccb_us) in SONAR_CALLBACKS_TRIPLE.items():
                dmin = us_to_ticks(dmin_us)
                dmax = us_to_ticks(dmax_us)
                Ccb = us_to_ticks(Ccb_us)
                Ta = start_time_tick + choose_delay(dmin, dmax)
                enqueue_future_event(Ta, cb_name, Ccb, "ReadSonar", start_time_tick)
        else:
            dmin_us, dmax_us, Ccb_us = SENSOR_CALLBACKS_SINGLE["ReadSonar"]
            dmin = us_to_ticks(dmin_us)
            dmax = us_to_ticks(dmax_us)
            Ccb = us_to_ticks(Ccb_us)
            Ta = start_time_tick + choose_delay(dmin, dmax)
            enqueue_future_event(Ta, "ReadSonar", Ccb, "ReadSonar", start_time_tick)

def pop_due_events(now_tick: int):
    """Enqueue di tutti gli eventi con Ta==now."""
    if not future_events:
        return
    due = [e for e in future_events if e[0] == now_tick]
    if not due:
        return
    future_events[:] = [e for e in future_events if e[0] != now_tick]
    for Ta_tick, cb_id, src, Ccb_tick in due:
        aper_q.append({"id": cb_id, "src": src, "remaining": Ccb_tick, "arrival": Ta_tick, "C": Ccb_tick})


H_tick = us_to_ticks(H)
ps_name_tick, Cs_tick, Ts_tick = PS_ticks

while time < H_tick:

    # 1) arrivi callback aperiodiche
    pop_due_events(time)

    # 2) release job periodici normali
    for name, C, T in tasks_ticks:
        if time % T == 0:
            release_times[name].append(time)
            jobs.append({
                "id": job_id_counter,
                "name": name,
                "remaining": C,
                "period": T,
                "release": time,
            })
            job_id_counter += 1

    # 3) rilascio PS (job-based!)
    if time % Ts_tick == 0:
        release_times[ps_name].append(time)
        # Crea job PS solo se c'è lavoro pendente ORA (Polling Server puro)
        if len(aper_q) > 0:
            ps_job = {"remaining": Cs_tick, "period": Ts_tick, "release": time}
        else:
            ps_job = None

    # 4) scelta RM tra:
    # - job periodico più prioritario (T min)
    # - PS job (se esiste) con periodo Ts
    ready_periodic = [j for j in jobs if j["remaining"] > 0]
    periodic_choice = min(ready_periodic, key=lambda j: j["period"]) if ready_periodic else None

    ps_ready = (ps_job is not None and ps_job["remaining"] > 0 and len(aper_q) > 0)

    run_ps = False
    if ps_ready:
        if periodic_choice is None:
            run_ps = True
        else:
            if Ts_tick < periodic_choice["period"]:
                run_ps = True
            elif Ts_tick == periodic_choice["period"]:
                run_ps = (not PERIODIC_WINS_TIE)
            else:
                run_ps = False

    # 5) esecuzione di 1 tick = DT_US
    if run_ps:
        ps_job["remaining"] -= 1

        # 1 tick di servizio all'aperiodico in testa
        aper_q[0]["remaining"] -= 1
        ps_exec_src[time] = aper_q[0]["src"]
        schedule.append((time, ps_name))

        if aper_q[0]["remaining"] == 0:
            aper_q.popleft()

        # Se non c'è più nulla da servire, il job PS termina SUBITO (come il tuo thread)
        if len(aper_q) == 0:
            ps_job = None

        # Se finisce budget, termina
        if ps_job is not None and ps_job["remaining"] == 0:
            ps_job = None

    elif periodic_choice is not None:
        # start job => genera callback una sola volta
        if periodic_choice["id"] not in started_job_ids:
            started_job_ids.add(periodic_choice["id"])
            schedule_callbacks_from_task(periodic_choice["name"], time)

        periodic_choice["remaining"] -= 1
        schedule.append((time, periodic_choice["name"]))

        if periodic_choice["remaining"] == 0:
            # end-cap all'ultimo tick eseguito = time
            finish_caps.append((time, periodic_choice["name"]))

    else:
        schedule.append((time, "IDLE"))

    # pulizia job completati
    jobs = [j for j in jobs if j["remaining"] > 0]
    time += 1


# ============================================================
# PLOT
# ============================================================

def _us_to_ms_formatter(x, _pos):
    v = x / 1000.0
    if abs(v - round(v)) < 1e-9:
        return str(int(round(v)))
    return f"{v:.3f}".rstrip("0").rstrip(".")


def plot_window(start_us: int, end_us: int):
    fig, ax = plt.subplots(figsize=(18, 6))

    # ordine RM (PS incluso): periodo crescente, PS sotto a parità
    period_of_us = {name: T_us for (name, _, T_us) in tasks}
    period_of_us[ps_name] = Ts

    present = sorted({task for _, task in schedule if task != "IDLE"})
    known = [t for t in present if t in period_of_us]
    unknown = [t for t in present if t not in period_of_us]

    known_sorted = sorted(known, key=lambda n: (period_of_us[n], 1 if n == ps_name else 0))
    task_names = known_sorted + unknown

    # layout
    lane = 1.35
    bar_h = 0.65
    bar_offset = 0.0
    N = len(task_names)

    y_line = {name: (N - 1 - i) * lane for i, name in enumerate(task_names)}

    # Headroom verticale per evitare che le frecce (callback) si sovrappongano al titolo
    Y_BOTTOM_MARGIN = 0.30 * lane
    Y_TOP_HEADROOM = 0.95 * lane
    y_min_plot = -Y_BOTTOM_MARGIN
    y_max_plot = max(y_line.values()) + bar_h + Y_TOP_HEADROOM

    # ============================================================
    # PALETTE COLORI COERENTE (catena funzionale)
    # ============================================================

    # Palette colori richiesta (Board2 + PS)
    # - Polling Server: verde chiaro
    # - Controller: giallo
    # - Giroscopio: arancione chiaro
    # - Supervisor: arancione scuro
    # - Sonar: rosso chiaro
    COLOR_PS_FALLBACK = "lightgreen"
    COLOR_CONTROLLER = "gold"
    COLOR_GYRO       = "#FFB74D"
    COLOR_COMM       = "darkorange"
    COLOR_SONAR      = "#E57373"

    # Sonar triplo (aperiodici): colori invariati
    COLOR_SONAR_LEFT  = "#009E73"   # bluish green (ben distinto)
    COLOR_SONAR_FRONT = "#56B4E9"   # sky blue
    COLOR_SONAR_RIGHT = "#CC79A7"   # reddish purple


    # --- task periodici ---
    task_color_map = {
        "ReadController": COLOR_CONTROLLER,
        "ReadGyroscope":  COLOR_GYRO,
        "ReadSonar":      COLOR_SONAR,
        "Supervisor":     COLOR_COMM,
        "PS":             COLOR_PS_FALLBACK,  # fallback / legenda
    }

    # --- callback / PS (stesso colore della sorgente logica) ---
    src_color = {
        "ReadController": COLOR_CONTROLLER,
        "ReadGyroscope":  COLOR_GYRO,

        # sonar triplo
        "ReadSonarLeft":  COLOR_SONAR_LEFT,
        "ReadSonarFront": COLOR_SONAR_FRONT,
        "ReadSonarRight": COLOR_SONAR_RIGHT,

        # sonar singolo (se SONAR_TRIPLE_CALLBACKS = False)
        "ReadSonar":      COLOR_SONAR,
    }

    ps_fallback_color = COLOR_PS_FALLBACK

    # 1) baseline
    for name in task_names:
        ax.hlines(y_line[name], start_us, end_us, colors="0.65", linewidth=1.0)

    # 2) barre esecuzione (clippate nella finestra)
    for t_tick, task in schedule:
        if task == "IDLE":
            continue
        if task not in y_line:
            continue
        y = y_line[task]

        t = ticks_to_us(t_tick)
        w = DT_US
        t0 = max(t, start_us)
        t1 = min(t + w, end_us)
        if t1 <= t0:
            continue
        w_clip = t1 - t0

        if task == ps_name:
            src = ps_exec_src.get(t_tick, None)
            c = src_color.get(src, ps_fallback_color)
            ax.broken_barh([(t0, w_clip)], (y + bar_offset, bar_h), facecolors=c, edgecolors="none")
        else:
            ax.broken_barh([(t0, w_clip)], (y + bar_offset, bar_h), facecolors=task_color_map[task], edgecolors="none")

    # 3) release
    for name in task_names:
        xs = release_times.get(name, [])
        if xs:
            y = y_line[name]
            xs_us = [ticks_to_us(x) for x in xs]
            xs_us = [x for x in xs_us if start_us <= x < end_us]
            if xs_us:
                ax.vlines(xs_us, y, y + bar_h + 0.20, colors="black", linewidth=1.3)

    # 4) end-cap fine job periodici (overlay)
    for t_last_tick, name in finish_caps:
        if name not in y_line:
            continue
        y = y_line[name]

        cap_h = bar_h
        cap_color = task_color_map.get(name, "black")

        t_last = ticks_to_us(t_last_tick)
        if not (start_us <= t_last < end_us):
            continue
        ax.broken_barh([(t_last, DT_US)], (y + bar_offset, cap_h), facecolors=cap_color, edgecolors="none", zorder=10)

    # 5) notifiche callback: frecce verso la corsia del PS (a Ta)
    #    cb_links: (src_cb, task_src, t_start_tick, Ta_tick, C_ticks, cb_id)
    ps_y = y_line.get(ps_name, 0.0)
    ARROW_GAP = 0.16                           # distanza dalla cima delle barre PS
    ARROW_LEN = 0.55                           # lunghezza desiderata freccia
    ARROW_LW = 2.2

    arrow_tip_y = ps_y + bar_h + ARROW_GAP
    # Limita la coda dentro al grafico (evita overlap con titolo/tight_layout)
    arrow_tail_y = min(arrow_tip_y + ARROW_LEN, y_max_plot - 0.08)

    for src_cb, _task_src, _t_start_tick, Ta_tick, _Ccb_tick, _cb_id in cb_links:
        Ta = ticks_to_us(Ta_tick)
        if not (start_us <= Ta < end_us):
            continue
        cb_color = src_color.get(src_cb, "black")
        ax.annotate(
            "",
            xy=(Ta, arrow_tip_y),
            xytext=(Ta, arrow_tail_y),
            arrowprops=dict(arrowstyle="->", color=cb_color, lw=ARROW_LW),
            zorder=11,
        )

    # assi
    ax.set_xlim(start_us, end_us)
    ax.set_xlabel("Time [ms]")

    mode = "worst-case" if USE_WORST_CASE_DELAY else f"random(seed={RANDOM_SEED})"
    sonar_mode = "triplo" if SONAR_TRIPLE_CALLBACKS else "singolo"
    ax.set_title(
        f"Rate Monotonic (+ Polling Server) Scheduling for Board2\n"
        f"View {start_us/1000:.0f}-{end_us/1000:.0f} ms",
        pad=14,
        fontweight="bold",
    )

    ax.set_yticks([y_line[n] for n in task_names])
    ax.set_yticklabels(task_names)
    ax.tick_params(axis="y", labelsize=9)

    # limita asse Y per avere spazio extra sopra
    ax.set_ylim(y_min_plot, y_max_plot)

    # ticks (in microsecondi) dentro finestra
    window_us = end_us - start_us
    if window_us <= 200_000:
        tick_step_us = 10_000
    elif window_us <= 1_000_000:
        tick_step_us = 50_000
    elif window_us <= 5_000_000:
        tick_step_us = 250_000
    else:
        tick_step_us = 500_000

    ax.set_xticks(range(start_us, end_us + 1, tick_step_us))
    ax.xaxis.set_major_formatter(FuncFormatter(_us_to_ms_formatter))

    # minor ticks: usa DT_US se non esplode il numero di tick
    minor_every_us = DT_US
    if window_us // max(minor_every_us, 1) <= 5000:
        ax.set_xticks(range(start_us, end_us + 1, minor_every_us), minor=True)
        ax.tick_params(axis="x", which="minor", bottom=False, labelbottom=False)

    # griglie
    ax.grid(True, which="minor", axis="x", linestyle="-", linewidth=0.10, color="0.90")
    ax.grid(True, which="major", axis="x", linestyle="-", linewidth=0.55, color="0.78")
    ax.grid(True, which="major", axis="y", linestyle="--", linewidth=0.35, color="0.82")

    # ============================================================
    # LEGENDA (basso a destra)
    # ============================================================

    legend_handles = []

    # periodici: patch
    for name in task_names:
        if name == ps_name:
            continue
        legend_handles.append(Patch(facecolor=task_color_map[name], edgecolor="none", label=f"{name} (periodic)"))

    # PS: patch per callback servita
    for src in CALLBACK_SOURCES:
        legend_handles.append(Patch(facecolor=src_color[src], edgecolor="none", label=f"PS serves {src}"))

    # frecce callback
    for src in CALLBACK_SOURCES:
        legend_handles.append(
            Line2D(
                [0],
                [0],
                color=src_color[src],
                marker=r"$\downarrow$",
                markersize=10,
                linestyle="None",
                label=f"Callback {src}",
            )
        )

    # release
    legend_handles.append(Line2D([0], [0], color="black", lw=1.3, label="Release (|)"))

    ax.legend(handles=legend_handles, loc="lower right", fontsize=8, framealpha=0.95)
    plt.tight_layout(rect=(0.06, 0, 1, 0.92))
    return fig


# 4 finestre sequenziali sull'iperperiodo
window_us = H // 4
for i in range(4):
    start_us = i * window_us
    end_us = (i + 1) * window_us if i < 3 else H
    fig = plot_window(start_us, end_us)
    plt.show()
    plt.close(fig)