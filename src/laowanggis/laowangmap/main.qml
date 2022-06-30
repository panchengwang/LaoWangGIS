import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import cn.pcgis 1.0

ApplicationWindow {
    id: app
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "lightgray"

    Component.onCompleted: {
        centerInScreen()
        console.log(screen.width)
    }

    MapControl{
        Component.onCompleted: {
            console.log("mapcontrol init finished")
        }
    }

    function centerInScreen(){
        width = screen.width * 0.75
        height = screen.height * 0.75
        x = (screen.width-width) * 0.5
        y = (screen.height-height)*0.5
    }
}
