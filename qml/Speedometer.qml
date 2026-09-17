import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: 300
    height: 300

    property int currentSpeed: 0

    Rectangle {
        id: bg
        anchors.fill: parent
        radius: width / 2
        color: "#2c3e50"
        border.color: "#34495e"
        border.width: 5

        // Speed Text
        Text {
            anchors.centerIn: parent
            text: root.currentSpeed.toString()
            font.pixelSize: 64
            font.bold: true
            color: "white"
        }

        // Unit Text
        Text {
            anchors.top: parent.verticalCenter
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            text: "km/h"
            font.pixelSize: 24
            color: "#bdc3c7"
        }

        // Circular progress indicator (simplified)
        Rectangle {
            id: indicator
            width: 10
            height: root.height / 2 - 20
            color: "#e74c3c"
            anchors.bottom: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            transformOrigin: Item.Bottom
            
            // Map 0-220 km/h to -135 to 135 degrees
            rotation: -135 + (root.currentSpeed / 220) * 270
            
            // Animation for smooth movement
            Behavior on rotation {
                NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
            }
        }
    }
}

