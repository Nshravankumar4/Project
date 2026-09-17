import QtQuick 2.15
import QtQuick.Shapes 1.15

Item {
    id: root
    width: 350
    height: 350

    property real value: 0
    property real maxValue: 240
    property string label: "km/h"
    property string title: "SPEED"
    property color glowColor: "#00d2ff"

    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: "#0a0a0a"
        border.color: "#1a1a1a"
        border.width: 15

        // Background Track
        Shape {
            anchors.fill: parent
            ShapePath {
                strokeColor: "#111111"
                strokeWidth: 10
                fillColor: "transparent"
                capStyle: ShapePath.RoundCap
                PathAngleArc {
                    centerX: root.width / 2; centerY: root.height / 2
                    radiusX: root.width / 2 - 25; radiusY: root.height / 2 - 25
                    startAngle: 140
                    sweepAngle: 260
                }
            }
        }

        // Active Value Arc
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
                    sweepAngle: (root.value / root.maxValue) * 260
                }
            }
        }

        Column {
            anchors.centerIn: parent
            spacing: -10
            
            Text {
                text: root.title
                color: "#666666"
                font.pixelSize: 14
                font.letterSpacing: 2
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }
            
            Text {
                text: Math.round(root.value).toString()
                color: "white"
                font.pixelSize: 82
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            Text {
                text: root.label
                color: "#888888"
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }
        }
    }
}

