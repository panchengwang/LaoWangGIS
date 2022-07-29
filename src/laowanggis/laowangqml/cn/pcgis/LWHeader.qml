import QtQuick 2.15
import QtQuick.Layouts 1.15
import cn.pcgis 1.0

Rectangle {
    property string caption: "Header"
    property string leftIcon: LWIconSet.icon_material_outlined_search
    property string rightIcon: LWIconSet.icon_material_outlined_account_circle
    property bool leftButtonVisible: true
    property bool rightButtonVisible: true

    signal leftClicked()
    signal rightClicked()

    implicitHeight: LWStyle.header_height
    color: LWStyle.header_color

    RowLayout{
        anchors.fill: parent
        spacing: 0
        LWButton{
            Layout.fillHeight: true
            icon: leftIcon
            radius: 0
            onClicked: {
                leftClicked()
            }
            visible: leftButtonVisible
        }

        Text{
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: caption
            font.pointSize: LWStyle.header_caption_point_size
            color: LWStyle.header_caption_color
        }

        LWButton{
            Layout.fillHeight: true
            icon: rightIcon
            label: ''
            radius: 0
            visible: rightButtonVisible
            onClicked: {
                rightClicked()
            }
        }
    }


}
