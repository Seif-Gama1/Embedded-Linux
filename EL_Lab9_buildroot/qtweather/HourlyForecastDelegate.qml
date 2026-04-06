import QtQuick 2.15

Rectangle {
    id: root
    property string time: "12 PM"
    property string temp: "20°C"
    property string feelsLike: ""
    property bool isCurrent: false

    width: 110
    height: 150
    radius: 15

    // Glassmorphism effect: transparent if not current, slight white overlay if current
    color: isCurrent ? Qt.rgba(1, 1, 1, 0.15) : "transparent"
    border.color: isCurrent ? Qt.rgba(1, 1, 1, 0.3) : "transparent"
    border.width: 1

    Column{
        anchors.centerIn: parent
        spacing: 12

        Text{
            text: root.time
            color: "white"
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text{
            text: root.temp
            color: "white"
            font.pixelSize: 26
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text{
            visible: root.feelsLike !== ""
            text: "Feels like " + root.feelsLike
            color: "white"
            font.pixelSize: 12
            opacity: 0.7
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }
}
