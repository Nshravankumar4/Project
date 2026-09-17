import QtQuick 2.15

Item {
    id: root
    width: 300
    height: 350
    
    property int currentIndex: 0
    property var menuTitles: ["DRIVE INFO", "TIRE PRESSURE", "ATTENTION LEVEL", "NAVIGATION"]
    property var menuContents: [
        "Trip: 45.2 km\nAvg: 12.5 km/L",
        "Front: 34 psi\nRear: 34 psi",
        "Driver Attention: HIGH\nTime: 1h 20m",
        "Head North on\nMain St 300m"
    ]

    Rectangle {
        anchors.fill: parent
        color: "#111111"
        radius: 20
        border.color: "#333333"
        border.width: 2
        opacity: 0.9

        Text {
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.menuTitles[root.currentIndex]
            color: "#00d2ff"
            font.pixelSize: 18
            font.bold: true
            font.letterSpacing: 2
        }

        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: 60
            width: parent.width - 40
            height: 1
            color: "#333"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            anchors.centerIn: parent
            text: root.menuContents[root.currentIndex]
            color: "white"
            font.pixelSize: 22
            horizontalAlignment: Text.AlignHCenter
            lineHeight: 1.5
        }

        // Paging dots
        Row {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Repeater {
                model: 4
                Rectangle {
                    width: 8; height: 8; radius: 4
                    color: root.currentIndex === index ? "#00d2ff" : "#444"
                }
            }
        }
    }
}

