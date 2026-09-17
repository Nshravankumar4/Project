import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: 600
    height: 40

    property int turnSignal: 0 // 0=off, 1=left, 2=right

    RowLayout {
        anchors.centerIn: parent
        spacing: 40

        // Left Blinker
        Text {
            text: "◄"
            color: root.turnSignal === 1 ? "#2ecc71" : "#222222"
            font.pixelSize: 36
        }

        // Dummy warning lights
        Text { text: "ABS"; color: "#f39c12"; font.pixelSize: 20; font.bold: true; opacity: 0.2 }
        Text { text: "BRAKE"; color: "#e74c3c"; font.pixelSize: 20; font.bold: true; opacity: 0.2 }
        Text { text: "ESP"; color: "#f1c40f"; font.pixelSize: 20; font.bold: true; opacity: 0.2 }

        // Right Blinker
        Text {
            text: "►"
            color: root.turnSignal === 2 ? "#2ecc71" : "#222222"
            font.pixelSize: 36
        }
    }
}

