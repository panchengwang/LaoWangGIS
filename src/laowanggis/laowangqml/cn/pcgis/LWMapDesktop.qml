import QtQuick 2.15
import cn.pcgis 1.0

LWApplicationWindow {
    id: desktop
    property var configuration: ({})

    header: LWHeader{
        caption: "LaowangGIS: A gis toolbox provided by a senior programmer"
        rightIcon: LWIconSet.icon_material_outlined_settings
        leftButtonVisible: false
        onRightClicked: {
//            connectionDlg.visible = true
        }
    }



    LWMapControl{
        anchors.fill: parent
        backgroundColor: "transparent"
        focus: true
        configuration: desktop.configuration

    }


    //    LWSQLConnectionDialog{
    //        id: connectionDlg
    //        modality: Qt.ApplicationModal
    //        visible: true
    //        onAccepted: {
    //            console.log(JSON.stringify(connection))
    //        }
    //    }

    LWSQLConnection{
        connectParameters: ({
                                'host':'127.0.0.1',
                                'port':'5432',
                                'dbname':'laowangdb',
                                'user':'pcwang',
                                'password':'123456'
                            })
    }

}
