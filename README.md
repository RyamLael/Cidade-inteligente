# Cidade Inteligente

A modular, real-time Smart City embedded system built on the **ESP32** microcontroller using **FreeRTOS** and the **Arduino framework**. The system simulates urban automation features including an automated vehicle access gate with optical barrier detection, adaptive street lighting based on ambient luminance, dual I2C LCD status displays, environmental telemetry (temperature and relative humidity), and an interactive web control dashboard served over a dedicated Wi-Fi access point via WebSockets and LittleFS.

---

## Features

* **Multi-Core FreeRTOS Architecture**: Deterministic task scheduling distributing real-time sensor acquisition and actuator control on Core 1, and networking / web server workloads on Core 0.
* **Thread-Safe State Management**: Centralized `SystemState` repository guarded by a FreeRTOS mutex (`StateLock`), ensuring atomic reads and writes across concurrent tasks.
* **Automated Access Gate**: Servo-driven barrier arm with optical laser barrier detection, potentiometer threshold calibration, automatic closing timer (2.5s), and manual web overrides.
* **Adaptive Street Lighting**: Ambient light monitoring via LDR with inverse PWM dimming (0–255), supporting both automatic dusk-to-dawn operation and manual brightness control.
* **Dual I2C LCD Displays**:
  * *Welcome Display (0x3F)*: Shows a customized greeting and dynamic city name.
  * *Sensor Display (0x3E)*: Displays real-time temperature and relative humidity.
* **Environmental Telemetry**: Periodic temperature and humidity sampling using a DHT11/DHT22 sensor with error detection and NaN filtering.
* **On-Board Web Server & WebSockets**: High-performance asynchronous HTTP server (`ESPAsyncWebServer`) serving static web assets from `LittleFS` and providing bi-directional real-time communication via WebSockets (`/ws`).
* **Interactive Mobile-First Web Dashboard**: Responsive frontend built with HTML5, CSS3, and vanilla JavaScript for real-time monitoring and actuation without external dependencies.
* **Dedicated Serial Diagnostic Suite**: Built-in interactive CLI menu allowing individual component hardware testing and an integrated I2C bus scanner.

---

## Hardware

| Component | Model / Type | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | ESP32 DOIT DevKit V1 | Dual-core Xtensa LX6 @ 240MHz, 320KB RAM, 4MB Flash; runs FreeRTOS scheduler, Wi-Fi SoftAP, and tasks. |
| **Environmental Sensor** | DHT11 / DHT22 | Measures ambient temperature (°C) and relative humidity (%). |
| **Gate Actuator** | Micro Servo (e.g. SG90) | Opens (5°) and closes (90°) the access gate barrier arm. |
| **Street Light** | High-Brightness LED | Simulates street lighting with 8-bit PWM brightness control. |
| **Optical Emitter** | 650nm Laser Diode Module | Emits a continuous laser beam across the gate entryway. |
| **Gate Light Sensor** | LDR (Light Dependent Resistor) | Detects laser beam interruption caused by passing vehicles or obstacles. |
| **Ambient Light Sensor** | LDR (Light Dependent Resistor) | Measures outdoor environmental illuminance for automatic lamp dimming. |
| **Threshold Potentiometer** | 10kΩ Rotary Potentiometer | Adjusts the analog sensitivity threshold for gate optical beam detection. |
| **Welcome Display** | 16x2 Character LCD (I2C: 0x3F) | Displays welcome messages and configurable city identification. |
| **Sensor Display** | 16x2 Character LCD (I2C: 0x3E) | Displays real-time temperature and humidity readings. |

---

## System Architecture

The software architecture follows a **Producer-Consumer pattern centered around a protected global state**. Peripheral drivers interact directly with hardware registers or low-level libraries. Application services encapsulate business logic and algorithms. FreeRTOS tasks execute periodic loops pinned to specific CPU cores, updating or reading the synchronized `SystemState`.

```
                      ┌─────────────────────────────────────────┐
                      │                HARDWARE                 │
                      │  DHT11   LDRs   Pot   Laser  Servo  LED │
                      └────┬───────┬─────┬──────┬──────▲─────▲──┘
                           │       │     │      │      │     │
                           ▼       ▼     ▼      │      │     │
┌─────────────────────────────┐ ┌─────────────┐ │      │     │
│         Drivers Layer       │ │AnalogDriver │ │      │     │
│  DHT11  ADC  LCD  LED  Servo│ └──────┬──────┘ │      │     │
└──────────────┬──────────────┘        │        │      │     │
               │                       ▼        │      │     │
┌──────────────▼────────────────────────────────┴──────┴─────┴──┐
│                      Application Services Layer               │
│  SensorService  AnalogService  LightingService  GateService   │
└──────────────────────────────┬────────────────────────────────┘
                               │ (Thread-Safe Mutex Lock)
                               ▼
┌───────────────────────────────────────────────────────────────┐
│                   Global State (SystemState)                  │
│       Shared Telemetry, Configuration, and Dirty Flags        │
└──────────────┬────────────────────────────────┬───────────────┘
               │                                │
               ▼                                ▼
┌─────────────────────────────┐  ┌──────────────────────────────┐
│         Task Layer          │  │       Web / Network Layer    │
│  SensorTask    AnalogTask   │  │  AsyncWebServer (Port 80)    │
│  LightingTask  GateTask     │  │  WebSocketHandler (/ws)      │
│  DisplayTask   (Core 1)     │  │  WebServerTask (Core 0)      │
└──────────────┬──────────────┘  └──────────────┬───────────────┘
               │                                │
               ▼                                ▼
       Dual 16x2 LCDs                    Web Browser (PWA)
     (Welcome & Sensors)                 Real-Time Control UI
```

### Drivers Layer

Drivers isolate low-level hardware interactions into modular, reusable C++ classes:

* **`ADCDriver`** (`include/drivers/ADC.h`, `src/drivers/ADC.cpp`): Configures GPIO analog inputs and reads raw 12-bit ADC samples (0–4095).
* **`DHT11Driver`** (`include/drivers/DHT11.h`, `src/drivers/DHT11.cpp`): Interfaces with the Adafruit DHT library, reads temperature and humidity values, and discards invalid NaN readings.
* **`LCDDriver`** (`include/drivers/LCD.h`, `src/drivers/LCD.cpp`): Wraps `LiquidCrystal_I2C`. Provides cursor navigation, backlight toggling, and formatted line-writing (`writeLine`) with space padding to prevent character remnants.
* **`LEDDriver`** (`include/drivers/LED.h`, `src/drivers/LED.cpp`): Manages LED output state and analog PWM dimming (0–255 duty cycle).
* **`ServoDriver`** (`include/drivers/Servo.h`, `src/drivers/Servo.cpp`): Manages angular servo positioning via `ESP32Servo`, providing designated `open()` (5°) and `close()` (90°) functions.
* **`WiFiDriver`** (`include/drivers/WiFi.h`, `src/drivers/WiFi.cpp`): Configures the ESP32 in SoftAP mode, assigns local network credentials, and monitors active client connections.

### Application Layer

Services implement domain logic independently of the execution model:

* **`AnalogService`** (`include/application/AnalogService.h`): Reads ambient light, gate beam light, and threshold potentiometer inputs. Updates `SystemState` and flags changes for web synchronization.
* **`DisplayService`** (`include/application/DisplayService.h`): Manages the dual LCD screens, rendering welcome messages and environmental telemetry when state flags indicate changes.
* **`GateService`** (`include/application/GateService.h`): Coordinates gate open/close commands and maintains gate position status.
* **`LightingService`** (`include/application/LightingService.h`): Dynamically maps ambient illuminance (0–4095) to inverse LED brightness (255–0). When manual control is active, applies requested brightness overrides.
* **`SensorService`** (`include/application/SensorService.h`): Periodically polls the DHT sensor, commits temperature and humidity readings to state, and raises display/web dirty flags.

### Task Layer

The system spawns six long-running FreeRTOS tasks pinned to specific cores to balance processing loads:

| Task Name | Core | Priority | Period | Stack Size | Function |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **`GateTask`** | 1 | 3 | 50 ms | 4096 B | Evaluates optical barrier detection against potentiometer threshold, controls servo angle, and manages 2.5s auto-close timeout. |
| **`AnalogTask`** | 1 | 3 | 50 ms | 4096 B | Continuously samples ambient LDR, gate LDR, and potentiometer analog channels. |
| **`LightingTask`** | 1 | 2 | 100 ms | 4096 B | Computes and updates street light PWM duty cycle based on ambient light or manual settings. |
| **`DisplayTask`** | 1 | 1 | 100 ms | 4096 B | Checks dirty flags and updates Welcome and Sensor LCD screens over I2C. |
| **`SensorTask`** | 1 | 1 | 1000 ms | 4096 B | Samples temperature and humidity from the DHT11 sensor. |
| **`WebServerTask`** | 0 | 1 | 100 ms | 8192 B | Cleans up disconnected WebSocket clients and broadcasts state updates to web clients when state changes. |

### Web Layer

* **HTTP Endpoints**:
  * `GET /`: Serves `index.html` from LittleFS storage.
  * `GET /style.css`, `GET /app.js`: Serves frontend stylesheets and scripts.
  * `GET /api/status`: Returns a RESTful JSON snapshot of the entire system state.
* **WebSocket Server**:
  * Endpoint: `ws://192.168.4.1/ws`
  * Automatically pushes system state on client connection.
  * Broadcasts delta updates whenever `g_systemState.webStateChanged` is raised.
  * Receives asynchronous JSON action commands from connected clients.

---

## Project Structure

```
Cidade Inteligente/
├── data/                             # LittleFS web assets
│   ├── app.js                        # WebSocket client and UI event handlers
│   ├── index.html                    # Responsive dashboard markup
│   └── style.css                     # Mobile-first CSS styling
├── docs/                             # Architecture blueprints and diagrams
│   ├── arquitetura.md                # System architecture documentation
│   ├── arquitetura_cidade_inteligente.md.pdf
│   └── diagrama.drawio               # System block diagrams
├── include/                          # Header files
│   ├── Config.h                      # Pinout assignments and system constants
│   ├── StateLock.h                   # Mutex synchronization macros
│   ├── SystemState.h                 # Global state structure definition
│   ├── application/                  # Business logic services
│   │   ├── AnalogService.h
│   │   ├── DisplayService.h
│   │   ├── GateService.h
│   │   ├── LightingService.h
│   │   ├── SensorService.h
│   │   └── web/                      # Web and serialization components
│   │       ├── HttpRoutes.h
│   │       ├── JsonSerializer.h
│   │       ├── WebServerService.h
│   │       └── WebSocketHandler.h
│   ├── debug/                        # Diagnostic menu & test suites
│   │   ├── DebugRunner.h
│   │   ├── drivers/                  # Component test harnesses
│   │   │   ├── ADCDebug.h
│   │   │   ├── DHT11Debug.h
│   │   │   ├── LCDDebug.h
│   │   │   ├── LEDDebug.h
│   │   │   ├── ServoDebug.h
│   │   │   └── WiFiDebug.h
│   │   └── tools/
│   │       └── I2CScannerDebug.h     # Bus diagnostic scanner
│   ├── drivers/                      # Hardware abstraction drivers
│   │   ├── ADC.h
│   │   ├── DHT11.h
│   │   ├── LCD.h
│   │   ├── LED.h
│   │   ├── Servo.h
│   │   └── WiFi.h
│   └── tasks/                        # FreeRTOS task declarations
│       ├── AnalogTask.h
│       ├── DisplayTask.h
│       ├── GateTask.h
│       ├── LightingTask.h
│       ├── SensorTask.h
│       ├── TaskManager.h
│       └── WebServerTask.h
├── src/                              # C++ implementation files
│   ├── main.cpp                      # FreeRTOS initialization and entrypoint
│   ├── SystemState.cpp               # Global state instance and mutex definition
│   ├── application/                  # Service implementations
│   ├── debug/                        # Diagnostic implementations
│   ├── drivers/                      # Driver implementations
│   └── tasks/                        # FreeRTOS task loop implementations
├── platformio.ini                    # PlatformIO project configuration
├── LICENSE                           # Project license (MIT)
└── README.md                         # Project documentation
```

---

## System State

Cross-task communication is coordinated through the global structure `SystemState` (`include/SystemState.h`):

```cpp
struct SystemState
{
    float temperature;              // Ambient temperature in °C
    float humidity;                 // Relative humidity percentage
    uint16_t ambientLight;          // Ambient LDR ADC reading (0-4095)
    uint16_t gateLight;             // Gate barrier LDR ADC reading (0-4095)
    uint16_t gateThreshold;         // Gate sensitivity potentiometer reading
    bool gateOpen;                  // Current physical gate status
    bool manualGateControl;         // Manual gate override flag
    bool gateOpenRequest;           // Web open command trigger
    bool gateCloseRequest;          // Web close command trigger
    uint8_t streetLightBrightness;  // Current PWM duty cycle (0-255)
    bool manualLightingControl;     // Manual lighting override flag
    char cityName[17];              // Configured city name (max 16 chars + null)
    bool cityNameChanged;           // LCD welcome display dirty flag
    bool sensorDisplayChanged;      // LCD sensor display dirty flag
    bool webStateChanged;           // WebSocket broadcast dirty flag
    bool brightnessChanged;         // Street light refresh dirty flag
};
```

Access across tasks is guarded by the synchronization macros defined in `include/StateLock.h`:

* `STATE_LOCK()`: Invokes `xSemaphoreTake(g_stateMutex, portMAX_DELAY)`. Blocks until the mutex is acquired.
* `STATE_UNLOCK()`: Invokes `xSemaphoreGive(g_stateMutex)`. Releases the lock.

---

## Data Flow

The following lifecycle represents the real-time sensor-to-cloud data progression:

```
[ Physical Sensors ]
         │
         ▼
[ Hardware Drivers ] (ADC, DHT11)
         │
         ▼
[ Application Services ] (AnalogService, SensorService)
         │
         ▼  (STATE_LOCK / Mutex)
[ SystemState ] ──► Updates values & sets webStateChanged = true
         │
         ▼
[ WebServerTask ] ──► Detects webStateChanged dirty flag
         │
         ▼
[ JsonSerializer ] ──► Serializes SystemState to JSON string
         │
         ▼
[ WebSocketHandler ] ──► Calls webSocket.textAll(jsonString)
         │
         ▼  (ws://192.168.4.1/ws)
[ Frontend app.js ] ──► Receives JSON event & executes updateUI()
         │
         ▼
[ DOM Rendering ] ──► Real-time gauges, status badges, and switches updated
```

---

## Frontend

The user interface is hosted on the ESP32's LittleFS flash storage and loaded directly in any web browser connecting to the Wi-Fi Access Point:

* **`index.html`**: Structured with an application header, real-time connection status pill, and collapsible accordion cards:
  * *City Name Card*: Form input and save button to modify the city name rendered on the physical Welcome LCD.
  * *Lighting Card*: Visual status of the street lights with toggle buttons.
  * *Gate Control Card*: Status badge (Open / Closed) with manual override buttons.
  * *Sensors Card*: Live telemetry displays for temperature, humidity, ambient light, and gate optical barrier readings.
* **`style.css`**: Mobile-optimized CSS styled with modern typography (Inter), rounded card components, smooth transitions, and distinct semantic status colors (`#22c55e` green for open/online, `#dc2626` red for closed/alerts, `#facc15` yellow for active lighting).
* **`app.js`**:
  * Opens and maintains persistent WebSocket connection to `ws://<host>/ws`.
  * Handles automatic reconnection with exponential backoff on disconnect.
  * Updates UI elements reactively upon receiving state JSON payloads.
  * Dispatches action commands (`set_city`, `open_gate`, `close_gate`, `request_state`) over the WebSocket channel.

---

## WebSocket Protocol

### Client-to-ESP32 Commands

The frontend dispatches commands formatted as JSON objects:

| Command | JSON Payload Example | Description |
| :--- | :--- | :--- |
| `set_city` | `{"command":"set_city","city":"Sobral"}` | Updates the city name displayed on the Welcome LCD screen. |
| `open_gate` | `{"command":"open_gate"}` | Manually forces the access gate to open (5° servo angle). |
| `close_gate` | `{"command":"close_gate"}` | Manually forces the access gate to close (90° servo angle). |
| `auto_gate` | `{"command":"auto_gate"}` | Resets manual gate override, restoring automatic optical detection. |
| `set_brightness` | `{"command":"set_brightness","brightness":180}` | Switches to manual lighting control and sets street light PWM duty cycle (0–255). |
| `auto_lighting` | `{"command":"auto_lighting"}` | Restores automatic LDR-based lighting dimming. |
| `request_state` | `{"command":"request_state"}` | Requests an immediate full-state JSON broadcast from the ESP32. |

### ESP32-to-Client State Broadcast

The ESP32 broadcasts the following JSON schema whenever system state changes:

```json
{
  "city": "Sobral",
  "temperature": 26.5,
  "humidity": 58.0,
  "ambientLight": 1420,
  "gateLight": 3890,
  "gateThreshold": 2100,
  "gateOpen": false,
  "manualGateControl": false,
  "streetLightBrightness": 166,
  "manualLightingControl": false
}
```

#### Field Reference

| Field | Type | Description |
| :--- | :--- | :--- |
| `city` | `string` | Current city name displayed on the Welcome LCD. |
| `temperature` | `float` | Ambient temperature in degrees Celsius. |
| `humidity` | `float` | Relative humidity percentage (0–100%). |
| `ambientLight` | `integer` | Raw 12-bit ADC reading of the ambient light LDR (0–4095). |
| `gateLight` | `integer` | Raw 12-bit ADC reading of the gate laser beam LDR (0–4095). |
| `gateThreshold` | `integer` | Raw 12-bit ADC reading of the threshold potentiometer (0–4095). |
| `gateOpen` | `boolean` | `true` if the gate is physically open; `false` if closed. |
| `manualGateControl` | `boolean` | `true` if gate is currently controlled manually via web. |
| `streetLightBrightness` | `integer` | Current PWM duty cycle applied to the street light LED (0–255). |
| `manualLightingControl` | `boolean` | `true` if lighting is manually overridden; `false` for auto-dimming. |

---

## Building the Project

### Requirements

* [VS Code](https://code.visualstudio.com/) with the [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode) or [PlatformIO Core (CLI)](https://docs.platformio.org/en/latest/core/installation/index.html).
* USB-to-UART cable compatible with the ESP32 DevKit board.

### PlatformIO Installation

Install PlatformIO CLI using Python:

```bash
pip install -U platformio
```

### Clone Repository

```bash
git clone https://github.com/RyamLael/Cidade-inteligente.git
cd "Cidade-inteligente"
```

### Build

Compile the firmware and verify all dependencies:

```bash
pio run
```

### Upload Firmware

Connect the ESP32 to your computer via USB and upload:

```bash
pio run -t upload
```

### Upload Filesystem

Upload the web dashboard assets (`data/index.html`, `data/style.css`, `data/app.js`) to LittleFS flash memory:

```bash
pio run -t uploadfs
```

---

## Debug System

The project includes an interactive diagnostic test suite (`include/debug/DebugRunner.h`) that can be invoked via serial terminal (115200 baud) during hardware bring-up:

```text
====================
DEBUG MENU
====================
1 - DHT11
2 - Servo
3 - LCD
4 - I2C Scanner
5 - ADC
6 - WiFi
7 - LED

Choose option:
```

### Diagnostic Modules

* **`DebugRunner`**: Presents the interactive console menu and routes execution to the selected test harness.
* **`ADCDebug`**: Continuously reads the ambient light LDR analog channel and prints raw ADC values to serial.
* **`DHT11Debug`**: Reads and outputs validated temperature and humidity metrics every 2 seconds.
* **`LCDDebug`**: Initializes both LCDs (0x3F and 0x3E) over I2C, displaying counter increments and simulated sensor readings.
* **`LEDDebug`**: Sweeps LED duty cycle from 0 to 255 and back in steps of 15 every 100ms.
* **`ServoDebug`**: Steps the gate servo through angles (5°, 45°, 90°, 135°, 180°) and executes gate open/close sequences.
* **`WiFiDebug`**: Starts the SoftAP interface and periodically prints the count of connected client devices.
* **`I2CScannerDebug`**: Sweeps all valid 7-bit I2C addresses (1 to 126) on SDA pin 21 and SCL pin 22, printing detected device hex addresses.

---

## Configuration

All hardware pinouts, network parameters, and system constants are configured in `include/Config.h`:

### Pin Assignments

| Symbol | GPIO Pin | Connected Component |
| :--- | :---: | :--- |
| `PIN_DHT11` | 4 | DHT11 / DHT22 Data line |
| `PIN_DHT22` | 4 | DHT22 Compatibility alias |
| `PIN_SERVO` | 18 | Gate barrier servo PWM control |
| `PIN_LED_POSTE` | 19 | Street light LED PWM output |
| `PIN_LASER` | 23 | Gate laser diode emitter control |
| `PIN_I2C_SDA` | 21 | I2C bus serial data |
| `PIN_I2C_SCL` | 22 | I2C bus serial clock |
| `PIN_LDR_AMBIENT` | 34 | Ambient light photoresistor (ADC1_CH6) |
| `PIN_LDR_GATE` | 35 | Gate laser barrier photoresistor (ADC1_CH7) |
| `PIN_POT_GATE` | 32 | Gate sensitivity potentiometer (ADC1_CH4) |

### Wi-Fi Configuration

| Parameter | Default Value | Description |
| :--- | :--- | :--- |
| `WIFI_SSID` | `"CidadeInteligente"` | SoftAP Network SSID |
| `WIFI_PASSWORD` | `"1cidade23456"` | SoftAP WPA2-PSK passphrase |

### System Constants

| Constant | Value | Description |
| :--- | :---: | :--- |
| `LCD_WELCOME_ADDRESS` | `0x3F` | I2C address for Welcome LCD |
| `LCD_SENSOR_ADDRESS` | `0x3E` | I2C address for Sensor LCD |
| `ADC_RESOLUTION` | `12` | ESP32 analog resolution (0–4095 range) |

---

## Screenshots

<!-- Add dashboard and hardware setup screenshots here -->
> _Placeholders for hardware build and web dashboard screenshots:_
> 
> ![Dashboard Overview](docs/imagens/dashboard_mockup.png)
> *Web Dashboard Interface*
> 
> ![Hardware Prototype](docs/imagens/hardware_prototype.png)
> *ESP32 Smart City Bench Prototype*

---

## Future Improvements

* [ ] **Non-Volatile Storage (NVS)**: Persist customized city names and gate calibration threshold settings across reboots.
* [ ] **Wi-Fi Station (STA) Mode with Fallback**: Enable connection to an external Wi-Fi router with automatic fallback to SoftAP mode.
* [ ] **Hardware Interrupt for Gate Barrier**: Transition from 50ms polling to GPIO edge interrupt for sub-millisecond optical barrier trigger latency.
* [ ] **MQTT / Cloud Telemetry Integration**: Add MQTT publishing support for integration with Home Assistant or AWS IoT Core.
* [ ] **Over-The-Air (OTA) Updates**: Implement firmware updates through the web interface.
* [ ] **NTP / Real-Time Clock (RTC)**: Synchronize clock via NTP to implement time-of-day lighting schedules.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Copyright (c) 2026 Ryam Lael
