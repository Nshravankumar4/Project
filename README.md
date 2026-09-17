# Automotive Cluster - Complete Real-World Project

This project is a complete, multi-process end-to-end example designed specifically for the **C++ + Qt/QML + Automotive Cluster** interview preparation root map.

## Architecture

To match a real **QNX / Automotive** environment, this project is split into **Two Processes** that communicate via **IPC (Inter-Process Communication)**:

1. **`VehicleService` (The Server)**
   * Simulates a background QNX daemon reading CAN bus data.
   * Runs a `QLocalServer` (Socket IPC) to broadcast data.
   * Proves your knowledge of: **Processes**, **Sockets**, **C++17**.

2. **`AutomotiveCluster` (The GUI Client)**
   * The actual Dashboard UI.
   * Connects to the IPC socket using `QLocalSocket` on a **background thread**.
   * Uses **MVVM** to bridge the IPC data to the QML UI.

### How it aligns with your JD:

- **IPC Mechanism (Socket / D-Bus)**: `VehicleService` and `AutomotiveCluster` communicate using `QLocalSocket`. 
- **Process & Multi Threads**: The GUI runs in one process. The Service runs in another. Inside the GUI, the IPC client (`CanSimulator.cpp`) runs on a dedicated `QThread` so network delays don't freeze the QML UI.
- **Design Patterns (MVVM)**: `ClusterViewModel.cpp` connects the raw IPC data to the QML View using `Q_PROPERTY`.
- **C++17/20**: Usage of smart pointers (`std::unique_ptr`), lambdas for thread connections, and `<random>`.
- **Qt/QML GUI**: `main.qml` and `Speedometer.qml` use QtQuick, Layouts, and Animations.

## How to Build and Run

### Option 1: Qt Creator (Recommended)
1. Open Qt Creator.
2. Select `File` -> `Open File or Project...`
3. Select the `CMakeLists.txt` file in this directory.
4. Build the project (Ctrl+B).
5. **CRITICAL STEP:** You must run BOTH applications.
   * Run `VehicleService.exe` first. A console will open saying "IPC Server is running".
   * Then run `AutomotiveCluster.exe`. It will connect to the socket and the speedometer will start moving!

