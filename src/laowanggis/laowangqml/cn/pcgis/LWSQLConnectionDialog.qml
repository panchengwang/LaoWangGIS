import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

LWDialog{

    property var connectParameters:({
                                    'host':'127.0.0.1',
                                    'port':'5432',
                                    'dbname':'laowangdb',
                                    'user':'pcwang',
                                    'password':'123456'
                                })

    width: 450
    height: 250

    form: Flickable{
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
                id:tfHost
                Layout.fillWidth: true
                placeholderText: "IP or Domain name of PostGIS/LaowangSQL/PostgreSQL"
                text:connectParameters.host.trim()
            }


            LWLabel{
                text:"Port"
            }

            LWTextField{
                id: tfPort
                Layout.fillWidth: true
                placeholderText: "Port of PostGIS/LaowangSQL/PostgreSQL"
                text:connectParameters.port.trim()
            }


            LWLabel{
                text:"Database"
            }

            LWTextField{
                id: tfDBName
                Layout.fillWidth: true
                placeholderText: "Database Name of PostGIS/LaowangSQL/PostgreSQL"
                text:connectParameters.dbname.trim()
            }


            LWLabel{
                text:"User"
            }

            LWTextField{
                id:tfUser
                Layout.fillWidth: true
                placeholderText: "Username of PostGIS/LaowangSQL/PostgreSQL"
                text:connectParameters.user.trim()
            }


            LWLabel{
                text:"Password"
            }

            LWTextField{
                id:tfPassword
                Layout.fillWidth: true
                placeholderText: "Password of PostGIS/LaowangSQL/PostgreSQL"
                text:connectParameters.password.trim()
            }
        }
    }

    LWSQLConnection{
        id: sqlConnect
        connectParameters:({})
        onError:{
            console.log(errorMessage)
        }
    }

    function beforeAccepted(){
        connectParameters = {
            'host': tfHost.text.trim(),
            'port': tfPort.text.trim(),
            'dbname': tfDBName.text.trim(),
            'user': tfUser.text.trim(),
            'password': tfPassword.text.trim()
        }
        sqlConnect.connectParameters = connectParameters;
        return false
    }
}
