# 🚀 RoverSpazialeOS

**Real-time operating system for a space rover, built on FreeRTOS and STM32.**

RoverSpazialeOS is a dual-board, hard real-time control system for a four-wheeled space rover (A4WD3 platform). It runs on two **STM32G474RE** microcontrollers communicating over UART, coordinated through a GPIO-based synchronization handshake. The decision logic is auto-generated from **Simulink** state machines, while all RTOS tasks are scheduled with **Rate Monotonic** priority assignment under **FreeRTOS V10.3** (CMSIS-RTOS2 API).

---

## Table of Contents

- [Architecture Overview](#architecture-overview)
- [Board 1 — Actuation & Monitoring](#board-1--actuation--monitoring)
- [Board 2 — Sensing & Navigation](#board-2--sensing--navigation)
- [Inter-Board Communication](#inter-board-communication)
- [Scheduling & Schedulability](#scheduling--schedulability)
- [Degraded Mode](#degraded-mode)
- [Project Structure](#project-structure)
- [Building](#building)
- [Scheduling Visualization](#scheduling-visualization)
- [Documentation](#documentation)
- [License](#license)

---

## Architecture Overview

```
┌──────────────────────────┐    UART     ┌──────────────────────────┐
│        BOARD 1           │◄───────────►│        BOARD 2           │
│  STM32G474RE (LQFP-64)  │   460 800   │  STM32G474RE (LQFP-64)  │
│                          │    baud     │                          │
│  • PID motor control     │             │  • Remote controller     │
│  • Encoder read          │   GPIO      │  • Gyroscope (MPU-6050)  │
│  • Temperature sensor    │◄───────────►│  • Sonar (HC-SR04 ×3)   │
│  • Battery monitor       │  SYNC/ACK   │  • Polling Server        │
│  • Supervisor + Actions  │  handshake  │  • Supervisor + Actions  │
│  • LED actuation         │             │  • Degraded Supervisor   │
└──────────────────────────┘             └──────────────────────────┘
```

Both boards share a **global state bus** (`BUS_GlobalState`) composed of each board's local sensor state. The Supervisor tasks on each board run a Simulink-generated decision model that evaluates sensor validity, deadline misses, and environmental conditions to produce actuation decisions (motor setpoints, LED states, rover actions).

---

## Board 1 — Actuation & Monitoring

Board 1 is responsible for motor control, environmental monitoring, and high-level decision actuation.

| Task | Period | Priority | WCET | Description |
|------|--------|----------|------|-------------|
| **PID** | 20 ms (50 Hz) | High | 1 ms | Reads quadrature encoders, updates motor speeds via closed-loop PID control |
| **Supervisor** | 50 ms (20 Hz) | AboveNormal | 20 ms | Aggregates sensor data, runs Simulink decision model, actuates LEDs & setpoints |
| **ReadTemperature** | 200 ms (5 Hz) | Normal | 1 ms | Reads internal ADC temperature sensor |
| **ReadBattery** | 200 ms (5 Hz) | Low | 1 ms | Reads battery voltage via ADC, computes charge percentage |

**Drivers:** Quadrature encoders, DC motor H-bridge control (×4), A4WD3 LED driver, internal temperature ADC, battery voltage ADC.

---

## Board 2 — Sensing & Navigation

Board 2 handles external sensing, remote control input, and navigation-related data.

| Task | Period | Priority | WCET | Description |
|------|--------|----------|------|-------------|
| **PollingServer** | 10 ms (100 Hz) | High5 | 1 ms | Aperiodic task server — services sensor callback requests within a per-period budget |
| **ReadController** | 20 ms (50 Hz) | High | 0.2 ms | Reads remote controller pad input (joystick axes + buttons) |
| **ReadGyroscope** | 40 ms (25 Hz) | AboveNormal | 0.2 ms | Reads MPU-6050 gyroscope over I²C |
| **Supervisor** | 50 ms (20 Hz) | Normal | 20 ms | Runs Simulink decision model, sends/receives global state via UART |
| **ReadSonars** | 100 ms (10 Hz) | BelowNormal | 2 ms | Triggers and reads three HC-SR04 ultrasonic sensors (left, front, right) |

**Drivers:** MPU-6050 gyroscope (I²C), HC-SR04 ultrasonic sonar (×3), wireless pad receiver, DC motor control.

---

## Inter-Board Communication

- **Data link:** UART at 460 800 baud with CRC integrity checking and serialization/deserialization of the bus frame.
- **Startup synchronization:** A GPIO-based SYNC/ACK handshake ensures both boards begin their periodic task sets at the same logical tick, minimizing clock drift.
- **Health monitoring:** Each board monitors the communication link health and the remote board's status (sensor validity, deadline misses).

---

## Scheduling & Schedulability

All periodic tasks are assigned **Rate Monotonic** (RM) priorities — shorter period = higher priority. Schedulability is verified with the **Liu & Layland** utilization bound test.

Board 2 additionally features a **Polling Server** that handles aperiodic sensor callbacks (e.g., sonar echo completion) within a fixed budget per period, preserving the schedulability guarantees of the periodic task set.

The Python visualization scripts perform the RM schedulability test and generate Gantt-chart-style timeline plots:

| Script | Description |
|--------|-------------|
| `SchedulingBoard1.py` | RM simulation & timeline for Board 1 tasks |
| `SchedulingBoard2.py` | RM simulation & timeline for Board 2 periodic tasks |
| `SchedulingBoard2PS.py` | RM + Polling Server simulation for Board 2 (with aperiodic callbacks) |

---

## Degraded Mode

The system supports a **degraded operating mode** that can be triggered either automatically (sensor failure, deadline miss) or manually via the remote controller. In degraded mode:

- Board 2 switches to an alternative Simulink model (`Board2Degraded`) with a dedicated `SupervisorDeg` task.
- Actuation models are replaced by degraded-safe variants (`ActionsDegradedModel`).
- Board health monitoring logic adapts to the reduced sensor set.

---

## Project Structure

```
RoverSpazialeOS/
├── Board1/                         # STM32CubeIDE project for Board 1
│   ├── Board1.ioc                  # STM32CubeMX configuration
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── actions/            # Simulink-generated action model headers
│   │   │   ├── board1/             # Simulink-generated Board1 model headers
│   │   │   ├── boards_health/      # Simulink-generated health monitor
│   │   │   ├── bus/                # Bus data types (sensors, decision, states)
│   │   │   ├── constants/          # Scheduling constants (periods, WCETs)
│   │   │   ├── comunication_link_health/
│   │   │   ├── driver/             # Low-level hardware drivers
│   │   │   ├── driver_init/        # Driver initialization wrappers
│   │   │   ├── motors_health/      # Motor health monitoring
│   │   │   ├── red_leds_actuation/ # Red LED actuation model
│   │   │   ├── rover_temperature_health/
│   │   │   ├── synchronization/    # Inter-board sync (SYNC/ACK)
│   │   │   ├── stub/               # Stubs for simulation/testing
│   │   │   ├── test/               # Test utilities
│   │   │   └── wcet_estimation/    # WCET measurement helpers
│   │   └── Src/                    # Corresponding source files
│   ├── Drivers/                    # STM32 HAL & CMSIS drivers
│   └── Middlewares/                # FreeRTOS kernel
│
├── Board2/                         # STM32CubeIDE project for Board 2
│   ├── Board2.ioc                  # STM32CubeMX configuration
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── actions/            # Simulink-generated action model
│   │   │   ├── actions_degraded/   # Degraded-mode action model
│   │   │   ├── board2/             # Simulink-generated Board2 model
│   │   │   ├── board2_degraded/    # Degraded Board2 model
│   │   │   ├── board2_health/      # Board2 health monitor
│   │   │   ├── bus/                # Bus data types
│   │   │   ├── constants/          # Scheduling constants
│   │   │   ├── driver/             # Hardware drivers (MPU-6050, HC-SR04, pad)
│   │   │   ├── synchronization/    # Inter-board sync
│   │   │   └── ...
│   │   └── Src/
│   ├── Drivers/
│   └── Middlewares/
│
├── SchedulingBoard1.py             # RM scheduling simulation — Board 1
├── SchedulingBoard2.py             # RM scheduling simulation — Board 2
├── SchedulingBoard2PS.py           # RM + Polling Server simulation — Board 2
│
├── docs/                           # Doxygen-generated documentation
│   ├── Doxyfile
│   ├── html/
│   └── latex/
│
├── doxygen-awesome-css/            # Doxygen theme (doxygen-awesome)
│
├── FreeRTOS_V10.3_CMSIS2_SEGGER.patch        # SEGGER SystemView debug patch (Board 1)
├── FreeRTOS_V10.3_CMSIS2_SEGGER_Board2.patch  # SEGGER SystemView debug patch (Board 2)
└── LICENSE                                    # GNU GPLv3
```

---

## Building

### Prerequisites

- **STM32CubeIDE** (or any ARM GCC toolchain with STM32CubeMX code generation)
- **STM32G474RE** Nucleo or custom board (×2)

### Steps

1. Open `Board1/` and `Board2/` as separate STM32CubeIDE projects.
2. Build each project in **Debug** or **Release** configuration.
3. Flash Board 1 and Board 2 to their respective microcontrollers.
4. Connect the two boards via UART (LPUART1 @ 460800 baud) and the GPIO SYNC/ACK lines.

### SEGGER SystemView Debugging (Optional)

The `.patch` files in the repository root are **only** needed to enable [SEGGER SystemView](https://www.segger.com/products/development-tools/systemview/) tracing. They are **not** required for a normal build.

To apply them:

```bash
git apply FreeRTOS_V10.3_CMSIS2_SEGGER.patch              # Board 1
git apply FreeRTOS_V10.3_CMSIS2_SEGGER_Board2.patch       # Board 2
```

After applying, rebuild with the `SEGGER_BUILD=1` flag enabled in the project configuration.

---

## Scheduling Visualization

The scheduling scripts require Python 3 with `matplotlib`:

```bash
pip install matplotlib
```

Run a simulation:

```bash
# Board 1 — Rate Monotonic timeline
python SchedulingBoard1.py

# Board 2 — Rate Monotonic timeline
python SchedulingBoard2.py

# Board 2 — RM + Polling Server (aperiodic callbacks)
python SchedulingBoard2PS.py --dt-us 100
```

Each script prints the utilization factor and Liu & Layland bound, then displays an interactive Gantt chart of the task schedule over one hyperperiod.

---

## Documentation

Full API documentation is generated with **Doxygen** using the [doxygen-awesome](https://github.com/jothepro/doxygen-awesome-css) theme.

To regenerate:

```bash
cd docs
doxygen Doxyfile
```

Then open `docs/html/index.html` in a browser.

---

## License

This project is licensed under the **GNU General Public License v3.0** — see the [LICENSE](LICENSE) file for details.
