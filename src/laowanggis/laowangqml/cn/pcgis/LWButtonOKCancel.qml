import QtQuick 2.15
import QtQuick.Layouts 1.15
import cn.pcgis 1.0

Rectangle {
    id: control
    implicitHeight: LWStyle.header_height
    color: LWStyle.header_color

    signal accepted()
    signal rejected()


    RowLayout{
        anchors.fill: parent
        spacing: LWStyle.spacing
        anchors.margins: LWStyle.margin

        Item{
            Layout.fillWidth: true
        }

        LWButton{
            id: btnCancel
            Layout.fillHeight: true
            icon: LWIconSet.icon_material_outlined_close
            label: "Cancel"
            radius: 0
            onClicked: {
                control.rejected()
            }
        }

        LWButton{
            id: btnOk
            Layout.fillHeight: true
            icon: LWIconSet.icon_material_outlined_done
            label: 'Ok'
            radius: 0
            implicitWidth: btnCancel.width
            onClicked: {
                control.accepted()
            }
        }
    }


}
