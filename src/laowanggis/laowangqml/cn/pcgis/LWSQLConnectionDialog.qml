import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

LWDialog{



    Flickable{
        anchors.fill: parent
        anchors.margins: LWStyle.margin
        contentHeight: grid.height
        GridLayout{
            id: grid
            width: parent.width
            columns: 2
            columnSpacing: LWStyle.spacing

            LWLabel{
                text:"Host"
            }

            LWTextField{
                Layout.fillWidth: true
            }


            LWLabel{
                text:"Port"
            }

            LWTextField{
                Layout.fillWidth: true
            }


            LWLabel{
                text:"Database"
            }

            LWTextField{
                Layout.fillWidth: true
            }


            LWLabel{
                text:"User"
            }

            LWTextField{
                Layout.fillWidth: true
            }


            LWLabel{
                text:"Password"
            }

            LWTextField{
                Layout.fillWidth: true
                echoMode: TextInput.Password
            }
        }
    }
}
