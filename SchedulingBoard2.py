import matplotlib.pyplot as plt
from math import gcd
from functools import reduce
from matplotlib.lines import Line2D
from matplotlib.patches import Patch
import argparse
from matplotlib.ticker import FuncFormatter

# ============================================================
# CONFIGURAZIONE (Board2)
# ============================================================

# Risoluzione temporale simulazione/plot
# - La simulazione avanza a quanti di DT_US microsecondi.
# - Tutti i tempi di input (C, T) sono espressi in microsecondi.
TIME_QUANTUM_US_CHOICES = (10, 50, 100, 500)
DEFAULT_TIME_QUANTUM_US = 100

# Task set: (name, C, T)  [tutti in microsecondi]
# Nota: input forniti in millisecondi:
# - ReadController:  2ms,  periodo 20ms
# - ReadGyroscope:   4ms,  periodo 40ms
# - Supervisor:     15ms,  periodo 50ms
# - ReadSonar:      25ms,  periodo 100ms
tasks = [
    ("ReadController",  2_000,  20_000),
    ("ReadGyroscope",   2_000,  40_000),
    ("Supervisor",     15_000,  50_000),
    ("ReadSonar",      25_000, 100_000),
]


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


# -------------------------
# Utility functions
# -------------------------
def lcm(a, b):
    return a * b // gcd(a, b)

def hyperperiod(periods):
    return reduce(lcm, periods)


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
    for name, C_us, T_us in tasks:
        _ensure_multiple_of_dt_us(f"{name}.C", C_us)
        _ensure_multiple_of_dt_us(f"{name}.T", T_us)


validate_timebase_configuration()

# -------------------------
# Rate Monotonic ordering (priorità: periodo più piccolo)
# -------------------------
tasks = sorted(tasks, key=lambda x: x[2])
task_names = [t[0] for t in tasks]

# -------------------------
# Schedulability test (Liu & Layland) - sufficiente
# -------------------------
U = sum(C / T for _, C, T in tasks)
n = len(tasks)
U_ll = n * (2**(1/n) - 1)

print(f"Utilizzazione totale U = {U:.3f} ({U*100:.1f}%)")
print(f"Limite teorico RM = {U_ll:.3f} ({U_ll*100:.1f}%)")
print("✔ Test sufficiente: schedulabile" if U <= U_ll else "✘ Test non garantisce schedulabilità")

# -------------------------
# Simulation parameters
# -------------------------
H = hyperperiod([t[2] for t in tasks])   # iperperiodo (us)
H_tick = us_to_ticks(H)

print(f"\nRisoluzione simulazione DT = {DT_US} us")
print(f"Iperperiodo H = {H} us ({H/1000.0:.3f} ms)")

time = 0  # tick

schedule = []          # (t_tick, running_task) ogni DT_US
jobs = []              # lista job attivi

release_times = {name: [] for name, _, _ in tasks}   # rientro nello scheduler (release)

# fine job periodici: end-cap all'ultimo tick eseguito
finish_caps = []      # (t_last_exec_tick, task_name)

job_id_counter = 0

# -------------------------
# RM simulation (time-driven, step=DT_US)
# -------------------------
tasks_ticks = [(name, us_to_ticks(C), us_to_ticks(T)) for name, C, T in tasks]

while time < H_tick:

    # Release new jobs
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

    # Select highest priority ready job
    ready = [j for j in jobs if j["remaining"] > 0]

    if ready:
        current = min(ready, key=lambda j: j["period"])
        current["remaining"] -= 1
        schedule.append((time, current["name"]))

        # se ha finito esattamente ora (dopo aver consumato questo ms)
        if current["remaining"] == 0:
            # end-cap sull'ultimo tick eseguito = time
            finish_caps.append((time, current["name"]))
    else:
        schedule.append((time, "IDLE"))

    # Remove completed jobs
    jobs = [j for j in jobs if j["remaining"] > 0]

    time += 1

# -------------------------
# Plot scheduling (Board2-like)
# - baseline per task
# - barre dalla baseline
# - release: linea verticale nera
# - fine job: end-cap (overlay sull'ultimo ms)
# -------------------------

fig, ax = plt.subplots(figsize=(18, 6))

# ordine RM (periodo crescente)
task_names = [t[0] for t in tasks]
period_of = {name: T for name, _, T in tasks}
task_names = sorted(task_names, key=lambda n: period_of[n])

# layout
lane = 1.35
bar_h = 0.65
bar_offset = 0.0
N = len(task_names)

y_line = {name: (N - 1 - i) * lane for i, name in enumerate(task_names)}

Y_BOTTOM_MARGIN = 0.30 * lane
Y_TOP_HEADROOM = 0.60 * lane
y_min_plot = -Y_BOTTOM_MARGIN
y_max_plot = max(y_line.values()) + bar_h + Y_TOP_HEADROOM

# Palette colori richiesta (Board2)
# - Controller: giallo
# - Giroscopio: arancione chiaro
# - Supervisor: arancione scuro
# - Sonar: rosso chiaro
COLOR_CONTROLLER = "gold"
COLOR_GYRO = "#FFB74D"
COLOR_COMM = "darkorange"
COLOR_SONAR = "#E57373"

task_color_map = {
    "ReadController": COLOR_CONTROLLER,
    "ReadGyroscope": COLOR_GYRO,
    "ReadSonar": COLOR_SONAR,
    "Supervisor": COLOR_COMM,
}

# 1) baseline
for name in task_names:
    ax.hlines(y_line[name], 0, H, colors="0.65", linewidth=1.0)

# 2) barre esecuzione
for t_tick, task in schedule:
    if task == "IDLE":
        continue
    if task not in y_line:
        continue
    y = y_line[task]
    t_us = ticks_to_us(t_tick)
    ax.broken_barh([(t_us, DT_US)], (y + bar_offset, bar_h), facecolors=task_color_map[task], edgecolors="none")

# 3) release
for name in task_names:
    xs = release_times.get(name, [])
    if xs:
        y = y_line[name]
        xs_us = [ticks_to_us(x) for x in xs]
        ax.vlines(xs_us, y, y + bar_h + 0.20, colors="black", linewidth=1.3)

# 4) end-cap fine job (overlay)
for t_last_tick, name in finish_caps:
    if name not in y_line:
        continue
    y = y_line[name]
    t_last_us = ticks_to_us(t_last_tick)
    ax.broken_barh([(t_last_us, DT_US)], (y + bar_offset, bar_h), facecolors=task_color_map[name], edgecolors="none", zorder=10)

# assi
ax.set_xlim(0, H)
ax.set_xlabel("Time [ms]")
ax.set_title(
    "Rate Monotonic Scheduling for Board2",
    pad=14,
    fontweight="bold",
)

ax.set_yticks([y_line[n] for n in task_names])
ax.set_yticklabels(task_names)
ax.set_ylim(y_min_plot, y_max_plot)
ax.tick_params(axis="y", labelsize=10)

# ticks (in microsecondi)
H_us = H
if H_us <= 200_000:
    tick_step_us = 10_000
elif H_us <= 1_000_000:
    tick_step_us = 50_000
elif H_us <= 5_000_000:
    tick_step_us = 250_000
else:
    tick_step_us = 500_000

ax.set_xticks(range(0, H_us + 1, tick_step_us))

# Mostra i tick in millisecondi (x resta in microsecondi)
def _us_to_ms_formatter(x, _pos):
    v = x / 1000.0
    if abs(v - round(v)) < 1e-9:
        return str(int(round(v)))
    return f"{v:.3f}".rstrip("0").rstrip(".")

ax.xaxis.set_major_formatter(FuncFormatter(_us_to_ms_formatter))

# minor ticks: usa DT_US se non esplode il numero di tick
minor_every_us = DT_US
if H_us // max(minor_every_us, 1) <= 5000:
    ax.set_xticks(range(0, H_us + 1, minor_every_us), minor=True)
    ax.tick_params(axis="x", which="minor", bottom=False, labelbottom=False)

# griglie
ax.grid(True, which="minor", axis="x", linestyle="-", linewidth=0.10, color="0.90")
ax.grid(True, which="major", axis="x", linestyle="-", linewidth=0.55, color="0.78")
ax.grid(True, which="major", axis="y", linestyle="--", linewidth=0.35, color="0.82")

# legenda (basso a destra)
legend_handles = [
    Patch(facecolor=task_color_map[name], edgecolor="none", label=f"{name} (periodic)")
    for name in task_names
]
legend_handles.append(Line2D([0], [0], color="black", lw=1.3, label="Release (|)"))
ax.legend(handles=legend_handles, loc="lower right", fontsize=8, framealpha=0.95)

plt.tight_layout(rect=(0.04, 0.0, 1.0, 1.0))
plt.show()
