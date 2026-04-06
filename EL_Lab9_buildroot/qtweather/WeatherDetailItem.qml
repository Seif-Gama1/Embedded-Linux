import QtQuick
import QtQuick.Layouts

Item {
    id: root
    property string iconSource: ""
    property string labelText: ""
    property string valueText: ""

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight

    RowLayout{
        id: layout
        spacing: 15

        Image{
            source: root.iconSource
            sourceSize.width: 32
            sourceSize.height: 32
            Layout.alignment: Qt.AlignVCenter
        }

        Column{
            Text{
                text: root.labelText
                color: "white"
                font.pixelSize: 14
                opacity: 0.6
            }
            Text{
                text: root.valueText
                color: "white"
                font.pixelSize: 18
                font.bold: true
            }
        }
    }
}
