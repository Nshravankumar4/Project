import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    width: 1280
    height: 480
    visible: true
    title: qsTr("Hyundai Mobis Digital Cluster")
    color: "#050505" 

    // Telltales at the top
    Telltales {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        turnSignal: clusterViewModel.turnSignal
    }

    // Main 3-Zone Layout
    RowLayout {
        anchors.centerIn: parent
        spacing: 30

        // ZONE 1: Speedometer (Left)
        DialGauge {
            value: clusterViewModel.speed
            maxValue: 240
            title: "SPEED"
            label: "km/h"
            glowColor: "#00d2ff" // Cyan glow
        }

        // ZONE 2: ADAS Center View
        AdasCenter {
            adasDistance: clusterViewModel.adasDistance
        }

        // ZONE 3: RPM Tachometer (Right)
        DialGauge {
            value: clusterViewModel.rpm
            maxValue: 8000
            title: "POWER"
            label: "rpm"
            glowColor: "#ff3366" // Red/Pink glow
        }
    }

    // Bottom Status Bar
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 60
        color: "transparent"

        // PRND Gear Selector
        RowLayout {
            anchors.centerIn: parent
            spacing: 20
            
            Text { text: "P"; color: clusterViewModel.gear === "P" ? "#2ecc71" : "#444"; font.pixelSize: 28; font.bold: clusterViewModel.gear === "P" }
            Text { text: "R"; color: clusterViewModel.gear === "R" ? "#e74c3c" : "#444"; font.pixelSize: 28; font.bold: clusterViewModel.gear === "R" }
            Text { text: "N"; color: clusterViewModel.gear === "N" ? "#f1c40f" : "#444"; font.pixelSize: 28; font.bold: clusterViewModel.gear === "N" }
            Text { text: "D"; color: clusterViewModel.gear === "D" ? "#3498db" : "#444"; font.pixelSize: 32; font.bold: clusterViewModel.gear === "D" }
        }

        // Left Bottom (Temp / Range)
        Text {
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            text: "22°C   |   Range: " + clusterViewModel.range + " km"
            color: "#aaaaaa"
            font.pixelSize: 18
        }

        // Right Bottom (ODO)
        Text {
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            text: "ODO: " + clusterViewModel.odometer + " km"
            color: "#aaaaaa"
            font.pixelSize: 18
        }
    }
}
