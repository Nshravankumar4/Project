# Automotive Cluster - Hyundai Mobis Style Digital Cockpit

This project is a complete, production-grade **Multi-Process Automotive Digital Cluster** built with modern C++ and Qt/QML. It is designed specifically to demonstrate the skills required for an Automotive HMI/Middleware role (C++17, Qt/QML, IPC, Multithreading, MVVM).

## 🚀 Architecture: Dual-Process IPC

To simulate a real **QNX / Automotive Linux** environment, this project is split into two independent executables communicating via **Local Sockets (IPC)**:

### 1. `VehicleService` (The Middleware Server)
*   A headless background daemon simulating physical car hardware.
*   Runs a `QLocalServer` to broadcast a complex binary data stream every 100ms.
*   **Simulates:** Speed, RPM, Gear (PRND), Battery SOC, Odometer, Range, Turn Signals, ADAS Distance, Steering Wheel Menu Toggles, and Critical System Alerts.

### 2. `AutomotiveCluster` (The GUI Client)
*   The graphical Dashboard UI featuring a modern **3-Zone Layout** (Hyundai/Kia style).
*   **Multithreading:** The IPC Client (`CanSimulator.cpp`) runs on a dedicated `QThread`, deserializing the binary network stream without blocking the UI.
*   **MVVM Pattern:** `ClusterViewModel` acts as the bridge, exposing the background thread data to the QML frontend safely via `Q_PROPERTY`.

## 🎨 UI Features (QML)
*   **Procedural Graphics:** Glowing Speed and RPM gauges drawn purely using math and `QtQuick.Shapes`—no static image assets required!
*   **ADAS Center View:** A dynamic 3D-perspective road that animates a lead car based on the distance data from the IPC server.
*   **Interactive Info Menu:** A center screen overlay that cycles through Trip Info, Tire Pressure, and Navigation.
*   **Dynamic Alerts:** An overriding, flashing red popup system that triggers instantly when the IPC server broadcasts a warning (e.g., "SPEED WARNING!").
*   **Touch Events:** Click the dashboard to simulate steering wheel buttons and cycle the menus manually!

## 🛠️ How to Build and Run

**CRITICAL:** You must run BOTH applications for the cluster to work.

1. Open `CMakeLists.txt` in Qt Creator.
2. Build the project (Ctrl+B).
3. **Start the Server:** In Qt Creator's Run Settings, select `VehicleService`. Run it. A console will open saying *"VehicleService (IPC Server) is running"*.
4. **Start the GUI:** Leave the console open. Change Run Settings to `AutomotiveCluster` and run it. The GUI will instantly connect to the server and the car will come alive!

*(Note: Every source file in this project has a matching `.md` file right next to it explaining the code line-by-line for interview study purposes!)*
