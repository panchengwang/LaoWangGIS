import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: dialog
    property alias form: container.children

    width: 600
    height: 400

    signal accepted()
    signal rejected()

    title: "Database Connection Information"


    flags: Qt.Window

    ColumnLayout{
        anchors.fill: parent

        LWHeader{
            leftButtonVisible: false
            Layout.fillWidth: true
            caption: dialog.title
        }

        Rectangle{
            id: container
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        LWOKCancelButton{
            Layout.fillWidth: true
            onAccepted: {
                if(beforeAccepted()){
                    dialog.accepted()
                    dialog.visible = false
                }

            }
            onRejected: {
                dialog.rejected()
                dialog.visible = false
            }
        }
    }

    function centerInParent(){
        x = (screen.width-width) * 0.5
        y = (screen.height-height)*0.5
    }

    function beforeAccepted(){
        return true
    }

    Component.onCompleted: {
        centerInParent()
    }
}







