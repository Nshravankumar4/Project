import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: 600
    height: 40

    property int turnSignal: 0 // 0=off, 1=left, 2=right
    property bool flashState: false

    Timer {
        interval: 400 // Slightly faster flash
        running: root.turnSignal !== 0
        repeat: true
        onTriggered: root.flashState = !root.flashState
        onRunningChanged: if (running) root.flashState = true; else root.flashState = false
    }

    RowLayout {
        anchors.centerIn: parent
        spacing: 50

        // Left Blinker (Flashing + Clickable)
        Text {
            text: "◄"
            color: (root.turnSignal === 1 && root.flashState) ? "#00ff00" : "#333333"
            font.pixelSize: 42
            layer.enabled: true
            
            MouseArea {
                anchors.fill: parent
                onClicked: root.turnSignal = (root.turnSignal === 1) ? 0 : 1
            }
        }

        // Warning lights (Static)
        Text { text: "ABS"; color: "#f39c12"; font.pixelSize: 22; font.bold: true; opacity: 0.3 }
        Text { text: "BRAKE"; color: "#e74c3c"; font.pixelSize: 22; font.bold: true; opacity: 0.3 }
        Text { text: "ESP"; color: "#f1c40f"; font.pixelSize: 22; font.bold: true; opacity: 0.3 }

        // Right Blinker (Flashing + Clickable)
        Text {
            text: "►"
            color: (root.turnSignal === 2 && root.flashState) ? "#00ff00" : "#333333"
            font.pixelSize: 42
            layer.enabled: true
            
            MouseArea {
                anchors.fill: parent
                onClicked: root.turnSignal = (root.turnSignal === 2) ? 0 : 2
            }
        }
    }
}

