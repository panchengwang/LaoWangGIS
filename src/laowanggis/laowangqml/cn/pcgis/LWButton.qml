import QtQuick 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: button

    property string icon: ''
    property string label: 'button'

    signal clicked()

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight
    radius:5
    color: LWStyle.button_color

    MouseArea{
        anchors.fill:parent
        hoverEnabled: true
        onClicked: {
            button.clicked()
        }

        onEntered: {
            overlay.opacity = 0.1
        }

        onExited: {
            overlay.opacity = 0.0
        }
    }

    Rectangle{
        id: overlay
        anchors.fill: parent
        opacity: 0.0
        color: LWStyle.white
    }

    RowLayout{
        id: layout
        anchors.centerIn: parent
        Text{
            id: image
            text: LWIconSet.getIcon(icon)
            color: LWStyle.button_text_color
            font.family: LWIconSet.getFontName(icon)
            font.pointSize: LWStyle.button_icon_point_fize
            Layout.leftMargin: LWStyle.button_margins
            Layout.fillHeight: true
            verticalAlignment: Text.AlignVCenter
        }
        Text{
            id: text
            color: LWStyle.button_text_color
            font.pointSize: LWStyle.button_label_point_size
            Layout.rightMargin: LWStyle.button_margins
            Layout.fillHeight: true
            text: label
            verticalAlignment: Text.AlignVCenter
        }
    }


}
