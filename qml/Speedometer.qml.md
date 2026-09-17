# qml/Speedometer.qml - Explanation Guide

**Purpose:** This is a **Custom QML Component**. In automotive development, you reuse UI widgets (like gauges) everywhere. This file encapsulates the speedometer logic so it can be cleanly used in `main.qml`.

### Complete Code & Line-by-Line Explanation

```qml
import QtQuick 2.15
import QtQuick.Controls 2.15

// 1. Root Item: The base container for our custom component
Item {
    id: root
    width: 300
    height: 300

    // 2. Custom Properties
    // We define our own variable that people using this component can pass data into.
    // In main.qml, we bound this to 'clusterViewModel.speed'.
    property int currentSpeed: 0

    Rectangle {
        id: bg
        anchors.fill: parent
        radius: width / 2 // Circle shape
        color: "#2c3e50"
        border.color: "#34495e"
        border.width: 5

        // Speed Text in the middle
        Text {
            anchors.centerIn: parent
            // Convert the integer speed to a string for displaying
            text: root.currentSpeed.toString()
            font.pixelSize: 64
            font.bold: true
            color: "white"
        }

        // Unit Text label below the speed text
        Text {
            anchors.top: parent.verticalCenter
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            text: "km/h"
            font.pixelSize: 24
            color: "#bdc3c7"
        }

        // 3. The Speedometer Needle (Indicator)
        Rectangle {
            id: indicator
            width: 10
            height: root.height / 2 - 20
            color: "#e74c3c"
            
            // Anchor it to the center bottom so it rotates like a clock hand
            anchors.bottom: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            transformOrigin: Item.Bottom // Pivot point for rotation
            
            // 4. Mathematical Data Binding
            // We map the speed (0 to 220 km/h) to a rotation angle (-135 to +135 degrees)
            rotation: -135 + (root.currentSpeed / 220) * 270
            
            // 5. ANIMATIONS (Crucial for UI/HMI roles)
            // 'Behavior on rotation' tells QML: "Whenever the rotation value changes,
            // don't snap to the new value instantly. Instead, smoothly animate to it over 150ms."
            Behavior on rotation {
                NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
            }
        }
    }
}
```

