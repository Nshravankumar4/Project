# qml/main.qml - Explanation Guide

**Purpose:** This is the master root file for the QML Frontend. It coordinates the entire screen layout, overlays, and incorporates interactive `QtQuick.Controls` (Widgets) to prove UI mastery.

### Key QML Concepts Demonstrated Here:
1.  **Layouts (`RowLayout`, `ColumnLayout`):** Used to perfectly center and align the 3 Zones (Speedometer, Center ADAS, Tachometer) without hardcoding pixels.
2.  **Widgets / Controls (`QtQuick.Controls`):** We import controls to build the left-side interactive panel (`Button`, `Switch`, `Slider`, `ProgressBar`).
3.  **Property Binding (MVVM):** The QML UI is completely bound to `clusterViewModel` (e.g., `value: clusterViewModel.speed`).
4.  **Touch Interactivity:** `MouseArea` is used to capture manual screen clicks.

### The Left-Side Control Panel (Zone 1 Widgets)
```qml
// Zone 1 Widgets (Interactive Controls)
ColumnLayout {
    spacing: 15
    
    Button {
        text: root.isMph ? "USE KM/H" : "USE MPH"
        onClicked: root.isMph = !root.isMph // Instantly morphs math for gauges
    }

    Button {
        text: "RESET ODO"
        onClicked: clusterViewModel.odometer = 0 // Writes back to C++!
    }

    RowLayout {
        Text { text: "Lane Assist"; color: "white" }
        Switch { checked: true } // Toggle Widget
    }

    Slider {
        id: cruiseSlider
        from: 0; to: 160; value: 60 // Slider Widget
    }

    ProgressBar {
        value: 0.85 // Progress Widget (Battery Health)
    }
}
```

### The Telltales & Overlays
```qml
// Highest Z-index floating Alert popup
AlertPopup {
    anchors.centerIn: parent
    message: clusterViewModel.alertMessage
}
```

### Interview Talking Points for this file:
*   *"I didn't use absolute pixel positions (`x: 50, y: 100`). I used fluid `RowLayout` and `anchors` so the UI scales cleanly to any screen size."*
*   *"I demonstrated QML Controls by implementing a custom left-hand pane with Buttons, Sliders, and Switches that physically write data back to the C++ ViewModel."*
