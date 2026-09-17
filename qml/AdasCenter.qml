import QtQuick 2.15

Item {
    id: root
    width: 400
    height: 480

    property int adasDistance: 100

    // Background road glow
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#000000" }
            GradientStop { position: 1.0; color: "#001020" }
        }
    }

    // Left Lane Line
    Rectangle {
        width: 6
        height: 250
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        rotation: 25
        transformOrigin: Item.Top
    }

    // Right Lane Line
    Rectangle {
        width: 6
        height: 250
        color: "white"
        anchors.right: parent.right
        anchors.rightMargin: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        rotation: -25
        transformOrigin: Item.Top
    }

    // Lead Car (Mockup)
    Rectangle {
        width: 80
        height: 40
        radius: 10
        color: root.adasDistance < 30 ? "#ff3333" : "#888888" // Red if too close
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        // Move car up/down based on IPC distance data
        anchors.bottomMargin: 50 + (root.adasDistance * 1.5)
        
        Behavior on anchors.bottomMargin {
            NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
        }

        // Fake tail lights
        Rectangle { width: 15; height: 5; color: "red"; radius: 2; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.margins: 5 }
        Rectangle { width: 15; height: 5; color: "red"; radius: 2; anchors.bottom: parent.bottom; anchors.right: parent.right; anchors.margins: 5 }
    }

    // Our Car (Static mockup at the bottom of the screen)
    Rectangle {
        width: 120
        height: 60
        radius: 15
        color: "#ffffff"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30 // Moved up so it doesn't overlap PRND
        opacity: 0.8
    }
}
