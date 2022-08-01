import QtQuick 2.15
import QtQuick.Controls 2.15
import cn.pcgis 1.0
import QtQuick.Layouts 1.15

Rectangle {
    id: control
    property var data: ({})

    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        HorizontalHeaderView {
            id: horizontalHeader
            syncView: tableView
            Layout.fillWidth: true
        }

        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip:true
            model:LWModelSQLQuery{
                modelData: control.data
            }
            delegate:
                Text{
                    id: label
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: display
                }


        }
        LWHeader{
            Layout.fillWidth: true
        }
    }





}
