import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

LWDialog{

    Flow{
        anchors.fill: parent
        anchors.margins: LWStyle.margin
        GridLayout{
            width: parent.width
            columns: 2
            columnSpacing: LWStyle.spacing

            LWLabel{
                text:"host"
            }

            LWTextField{
                Layout.fillWidth: true
            }

        }
    }
}
