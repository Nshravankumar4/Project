import QtQuick 2.15

Item {
    id: root
    width: 500
    height: 120

    property string message: ""
    property bool isActive: message !== ""

    visible: isActive

    Rectangle {
        anchors.fill: parent
        radius: 15
        color: "#e74c3c" // Red alert background
        border.color: "#c0392b"
        border.width: 4
        
        // Pulsing animation
        SequentialAnimation on opacity {
            loops: Animation.Infinite
            running: root.isActive
            NumberAnimation { to: 0.7; duration: 500 }
            NumberAnimation { to: 1.0; duration: 500 }
        }

        Text {
            anchors.centerIn: parent
            text: "⚠️ " + root.message
            color: "white"
            font.pixelSize: 36
            font.bold: true
        }
    }
}

