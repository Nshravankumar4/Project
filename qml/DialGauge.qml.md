# qml/DialGauge.qml - Explanation Guide

**Purpose:** A modern, reusable gauge component for the Hyundai Mobis style cluster. It uses QML `Shape` to procedurally draw smooth glowing arcs without needing image assets.

### Complete Code & Line-by-Line Explanation

```qml
import QtQuick 2.15
import QtQuick.Shapes 1.15 // Required for advanced vector graphics (PathAngleArc)

Item {
    id: root
    width: 350
    height: 350

    // Properties that allow us to reuse this for both SPEED and RPM
    property real value: 0
    property real maxValue: 240
    property string label: "km/h"
    property string title: "SPEED"
    property color glowColor: "#00d2ff"

    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: "#0a0a0a" // Dark cluster background
        border.color: "#1a1a1a"
        border.width: 15

        // Background Track (The dark gray arc)
        Shape {
            anchors.fill: parent
            ShapePath {
                strokeColor: "#111111"
                strokeWidth: 10
                fillColor: "transparent"
                capStyle: ShapePath.RoundCap
                // Draws a partial circle (140 deg start, sweeping 260 deg)
                PathAngleArc {
                    centerX: root.width / 2; centerY: root.height / 2
                    radiusX: root.width / 2 - 25; radiusY: root.height / 2 - 25
                    startAngle: 140
                    sweepAngle: 260
                }
            }
        }

        // Active Value Arc (The glowing arc that fills up as speed increases)
        Shape {
            anchors.fill: parent
            ShapePath {
                strokeColor: root.glowColor
                strokeWidth: 10
                fillColor: "transparent"
                capStyle: ShapePath.RoundCap
                PathAngleArc {
                    centerX: root.width / 2; centerY: root.height / 2
                    radiusX: root.width / 2 - 25; radiusY: root.height / 2 - 25
                    startAngle: 140
                    // Math: Calculate how much of the 260-degree arc to fill based on current speed
                    sweepAngle: (root.value / root.maxValue) * 260
                }
            }
        }

        // Text Display in the center of the gauge
        Column {
            anchors.centerIn: parent
            spacing: -10
            
            Text {
                text: root.title // e.g. "SPEED"
                color: "#666666"
                font.pixelSize: 14
                font.letterSpacing: 2
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }
            
            Text {
                text: Math.round(root.value).toString() // Large digital number
                color: "white"
                font.pixelSize: 82
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            Text {
                text: root.label // e.g. "km/h"
                color: "#888888"
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }
        }
    }
}
```

