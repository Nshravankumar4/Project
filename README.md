# 🚗 Automotive Cluster - Hyundai Mobis Style Digital Cockpit

This project is a complete, production-grade **Multi-Process Automotive Digital Cockpit** built with modern C++ and Qt/QML. 

It is designed as an **End-to-End Interview Masterpiece** to prove absolute mastery over C++17, Multithreading, Inter-Process Communication (IPC), MVVM Architecture, and Advanced QML UI Design.

---

## 📂 Project Structure (Where is everything?)

To keep the architecture clean, the files are strictly separated by responsibility:

### 1. C++ Header Files (`.h`) - *The Definitions*
*   `src/services/MockCanServer.h` - Defines the IPC Server daemon.
*   `src/services/CanSimulator.h` - Defines the IPC Client and cross-thread signals.
*   `src/viewmodels/ClusterViewModel.h` - Defines the MVVM `Q_PROPERTY` bridges for QML.

### 2. C++ Source Files (`.cpp`) - *The Core Logic*
*   `src/VehicleServiceMain.cpp` - The `main()` entry point for the background hardware daemon.
*   `src/main.cpp` - The `main()` entry point for the GUI application.
*   `src/services/MockCanServer.cpp` - Generates fake vehicle data and broadcasts it via `QLocalSocket`.
*   `src/services/CanSimulator.cpp` - Runs on a `QThread`, receives socket data, and decodes binary packets.
*   `src/viewmodels/ClusterViewModel.cpp` - Formats the raw data and provides `WRITE` functions for UI buttons.

### 3. QML Files (`.qml`) - *The Graphical UI (Widgets & Layouts)*
*   `qml/main.qml` - The root Window containing the **3-Zone Layout** (`RowLayout`).
*   `qml/DialGauge.qml` - Procedural speedometer and tachometer using `QtQuick.Shapes`.
*   `qml/AdasCenter.qml` - 3D procedural road and lead-car rendering.
*   `qml/InfoMenu.qml` - The center screen overlay with map and trip data.
*   `qml/Telltales.qml` - The flashing neon turn signals at the top.
*   `qml/AlertPopup.qml` - The high Z-index red warning screen.

### 4. Study Guides (`.md`) - *Your Interview Cheat Sheets*
*   *Every single file listed above has a matching `.md` file right next to it containing a line-by-line interview explanation!*

---

## 🧠 End-to-End Flow (How it works)

If an interviewer asks you how the data flows from the car to the screen, this is your answer:

1.  **The CAN Bus (IPC Server):** `MockCanServer.cpp` acts as the physical car. It packs variables (Speed, Gear, RPM, ADAS) into a binary byte stream using `QDataStream` and broadcasts it over a QNX-style Local Socket.
2.  **The Receiver (Multithreading):** `CanSimulator.cpp` lives in the GUI app, but it runs on a completely separate background `QThread`. It catches the socket bytes, decodes them, and emits Qt Signals.
3.  **The ViewModel (MVVM):** `ClusterViewModel.cpp` catches those background signals via a thread-safe Queued Connection. It saves the data and emits `NOTIFY` signals to the frontend.
4.  **The Screen (QML):** The `qml/main.qml` file is bound directly to the ViewModel via `Q_PROPERTY`. When the data changes, the QML engine instantly repaints the specific gauge or telltale without any extra code!

---

## 🎯 Technical Topics Covered (Checklist)

This project explicitly implements the following requirements:

### ✅ Left-Side Layouts & QML Widgets (Controls)
You will find the **Zone 1 Left-Side Layout** in `qml/main.qml`. 
We used strict QML Layouts (`RowLayout`, `ColumnLayout`) to position elements cleanly. We also imported `QtQuick.Controls` (QML's version of Widgets) to create interactive **Buttons** ("USE MPH" and "RESET ODO"). Clicking these buttons triggers C++ `WRITE` properties!

### ✅ Touch Events & Interactivity
*   **Blinkers:** In `Telltales.qml`, the Left and Right arrows are wrapped in invisible `MouseArea` widgets. You can physically click them to trigger the neon flashing timer logic.
*   **Center Screen:** A `MouseArea` covers the ADAS view, allowing you to tap through the Info Pages manually.

### ✅ C++17 & Multithreading
We heavily utilized Modern C++ features: `std::unique_ptr` for memory-safe thread management, `auto`, Lambdas for timers, and the `<random>` STL library for data simulation.

### ✅ QNX IPC Architecture
By building this as **two separate executables** that talk via `QLocalSocket`, this completely mimics a QNX or Automotive Grade Linux environment where the UI process is strictly sandboxed away from the hardware driver process.

---

## 🛠️ How to Build and Run

**CRITICAL:** You must run BOTH applications to see the data flow!

1. Open `CMakeLists.txt` in Qt Creator and click **Run CMake**.
2. Build the project (Ctrl+B).
3. **Start the Server:** In Qt Creator's Run Settings, select `VehicleService`. Run it. A console will open saying *"VehicleService (IPC Server) is running"*.
4. **Start the GUI:** Leave the console open. Change Run Settings to `AutomotiveCluster` and run it. The GUI will instantly connect to the server! Click the left buttons and the blinkers to test the interactivity!
5. <img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/1b0c14c4-8119-4650-93ef-ee2f88c407e5" />

