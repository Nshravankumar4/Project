# qml/main.qml - Explanation Guide

**Purpose:** This is the root UI file for the Automotive Cluster. It defines the window layout and demonstrates QML Data Binding to C++ Properties.

### Complete Code & Line-by-Line Explanation

```qml
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

// 1. The main Window of our Application
Window {
    width: 800
    height: 480
    visible: true
    title: qsTr("Automotive Cluster Demo")
    color: "#1a1a1a" // Dark theme typical for clusters

    // 2. Top Status Bar
    Rectangle {
        id: topBar
        width: parent.width
        height: 40
        color: "transparent"

        Text {
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            
            // 3. QML DATA BINDING (Very Important)
            // We concatenate string text with our C++ property.
            // When C++ emits 'batterySocChanged', this entire text recalculates automatically!
            text: "Battery: " + clusterViewModel.batterySoc + "%"
            
            // We can also use JS logic in bindings. If battery is > 20%, make it green, else red.
            color: clusterViewModel.batterySoc > 20 ? "#2ecc71" : "#e74c3c"
            font.pixelSize: 18
            font.bold: true
        }
    }

    // 4. Layouts: RowLayout automatically spaces items horizontally
    RowLayout {
        anchors.centerIn: parent
        spacing: 50

        // 5. RPM Display (Simple Text-based Gauge)
        Rectangle {
            width: 200
            height: 200
            radius: 100 // Makes the rectangle a perfect circle
            color: "#34495e"
            
            Column {
                anchors.centerIn: parent
                spacing: 5
                
                Text {
                    // Data binding to C++ RPM property
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

        // 6. Custom QML Component Usage
        // We defined "Speedometer" in Speedometer.qml. QML automatically recognizes it.
        Speedometer {
            id: speedo
            // Bind the C++ speed property to the custom component's property
            currentSpeed: clusterViewModel.speed
        }
    }
}
```

