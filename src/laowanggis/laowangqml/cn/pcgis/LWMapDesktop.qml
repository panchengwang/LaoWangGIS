import QtQuick 2.15
import cn.pcgis 1.0

LWApplicationWindow {
    id: desktop
    property var configuration: ({})

    header: LWHeader{
        caption: "欢迎使用麓山老将为您倾情提供的GIS工具"
        rightIcon: LWIconSet.icon_material_outlined_settings
        leftButtonVisible: false
        onRightClicked: {
            connectionDlg.visible = true
        }
    }



    LWMapControl{
        anchors.fill: parent
        backgroundColor: "transparent"
        focus: true
        configuration: desktop.configuration
    }


    LWSQLConnectionDialog{
        id: connectionDlg
        modality: Qt.ApplicationModal
    }



}
