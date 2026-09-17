import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    id: root
    width: 1280
    height: 480
    visible: true
    title: qsTr("Hyundai Mobis Digital Cluster")
    color: "#050505" 



    // 0. Simulated Map Background (Optional "Navigation" layer)
    Rectangle {
        anchors.fill: parent
        color: "#0a192f"
        opacity: clusterViewModel.menuIndex === 3 ? 0.4 : 0.0 // Only show when Nav is selected
        Behavior on opacity { NumberAnimation { duration: 500 } }
        
        // Fake Map Grid
        Grid {
            anchors.fill: parent
            rows: 10; columns: 20
            Repeater {
                model: 200
                Rectangle { width: 64; height: 48; color: "transparent"; border.color: "#1e3a8a"; border.width: 1 }
            }
        }
    }

    // State for Zone 1 toggle
    property bool isMph: false

    // 1. Telltales Component
    Telltales {
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        turnSignal: clusterViewModel.turnSignal
    }

    // Main 3-Zone Layout
    RowLayout {
        anchors.centerIn: parent
        spacing: 30

        // ZONE 1: Speedometer & Controls Layout (Left Side)
        RowLayout {
            spacing: 20

            // Zone 1 Widgets (Interactive Controls)
            ColumnLayout {
                spacing: 15
                Layout.alignment: Qt.AlignVCenter
                
                Button {
                    text: root.isMph ? "USE KM/H" : "USE MPH"
                    font.pixelSize: 14
                    font.bold: true
                    palette.buttonText: "white"
                    palette.button: "#1e3a8a" // Blue button
                    onClicked: root.isMph = !root.isMph
                }

                Button {
                    text: "RESET ODO"
                    font.pixelSize: 14
                    font.bold: true
                    palette.buttonText: "white"
                    palette.button: "#e74c3c" // Red button
                    onClicked: clusterViewModel.odometer = 0 
                }

                // --- NEW QML WIDGETS ---
                
                // QML Switch (Toggle)
                RowLayout {
                    Text { text: "Lane Assist"; color: "white"; font.pixelSize: 14 }
                    Switch {
                        checked: true
                        onCheckedChanged: console.log("Lane Assist: " + checked)
                    }
                }

                // QML Slider (Cruise Control Speed)
                Text { text: "Cruise: " + Math.round(cruiseSlider.value) + " km/h"; color: "white"; font.pixelSize: 14 }
                Slider {
                    id: cruiseSlider
                    from: 0; to: 160; value: 60
                    width: 120
                }

                // QML ProgressBar (Simulated Battery Health)
                Text { text: "Battery Health"; color: "white"; font.pixelSize: 12 }
                ProgressBar {
                    value: 0.85 // 85% health
                    width: 120
                }
            }

            // Speedometer Gauge
            DialGauge {
                width: 350; height: 350
                value: root.isMph ? (clusterViewModel.speed * 0.621371) : clusterViewModel.speed
                maxValue: root.isMph ? 160 : 240
                title: "SPEED"
                label: root.isMph ? "mph" : "km/h"
                glowColor: "#00d2ff"
            }
        }

        // ZONE 2: Center View (ADAS + Info Menu)
        Item {
            width: 400
            height: 480
            
            // ADAS Center View
            AdasCenter {
                anchors.fill: parent
                adasDistance: clusterViewModel.adasDistance
            }

            // Info Menu (Overlays ADAS view)
            InfoMenu {
                anchors.centerIn: parent
                currentIndex: clusterViewModel.menuIndex
            }
            
            // Interactive touch for Center Zone
            MouseArea {
                anchors.fill: parent
                onClicked: clusterViewModel.menuIndex = (clusterViewModel.menuIndex + 1) % 4
            }
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

    // Floating Alert Popup (Highest Z-index, overlays everything)
    AlertPopup {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -100 // Slightly above center
        message: clusterViewModel.alertMessage
    }
}
