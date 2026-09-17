import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Automotive Cluster Demo")
    color: "#1a1a1a"

    // Top Bar (Battery, Info)
    Rectangle {
        id: topBar
        width: parent.width
        height: 40
        color: "transparent"

        Text {
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: "Battery: " + clusterViewModel.batterySoc + "%"
            color: clusterViewModel.batterySoc > 20 ? "#2ecc71" : "#e74c3c"
            font.pixelSize: 18
            font.bold: true
        }
    }

    RowLayout {
        anchors.centerIn: parent
        spacing: 50

        // RPM Display
        Rectangle {
            width: 200
            height: 200
            radius: 100
            color: "#34495e"
            
            Column {
                anchors.centerIn: parent
                spacing: 5
                
                Text {
                    // Data binding: automatically updates when clusterViewModel.rpm changes
                    text: clusterViewModel.rpm
                    color: "white"
                    font.pixelSize: 42
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }
                Text {
                    text: "RPM"
                    color: "#95a5a6"
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                }
            }
        }

        // Speedometer Custom Component
        Speedometer {
            id: speedo
            // Bind the QML property to the C++ Q_PROPERTY
            currentSpeed: clusterViewModel.speed
        }
    }
}

