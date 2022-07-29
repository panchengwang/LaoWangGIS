import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: dialog
    default property alias form: container.children
    title: "数据库连接"
    width: 400
    height: 300

    flags: Qt.Dialog

    ColumnLayout{
        anchors.fill: parent
        Rectangle{
            id: container
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        LWHeader{
            Layout.fillWidth: true
        }
    }
}







