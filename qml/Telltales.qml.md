# qml/Telltales.qml - Explanation Guide

**Purpose:** Defines the top bar of the cluster containing standard dashboard warning lights (Telltales). Demonstrates how IPC signals (like turn signals) can toggle UI visibility or colors.

### Complete Code & Line-by-Line Explanation

```qml
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: 600
    height: 40

    // IPC data bound from ViewModel (0=off, 1=left, 2=right)
    property int turnSignal: 0 

    RowLayout {
        anchors.centerIn: parent
        spacing: 40

        // Left Blinker
        Text {
            text: "◄"
            // If turnSignal == 1, color it bright green, else dark gray (off)
            color: root.turnSignal === 1 ? "#2ecc71" : "#222222"
            font.pixelSize: 36
        }

        // Dummy warning lights (In a real app, these would also be bound to IPC boolean properties)
        Text { text: "ABS"; color: "#f39c12"; font.pixelSize: 20; font.bold: true; opacity: 0.2 }
        Text { text: "BRAKE"; color: "#e74c3c"; font.pixelSize: 20; font.bold: true; opacity: 0.2 }
        Text { text: "ESP"; color: "#f1c40f"; font.pixelSize: 20; font.bold: true; opacity: 0.2 }

        // Right Blinker
        Text {
            text: "►"
            // If turnSignal == 2, color it bright green, else dark gray (off)
            color: root.turnSignal === 2 ? "#2ecc71" : "#222222"
            font.pixelSize: 36
        }
    }
}
```

