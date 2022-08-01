import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import cn.pcgis 1.0

ApplicationWindow {


    width: 720
    height: 540

    visible: true
    title: qsTr("Welcome to LaoWang GIS ! QQ: 593723812")
    color: "lightgray"

    Component.onCompleted: {
//        centerInScreen()
    }



    function centerInScreen(){
        width = screen.width * 0.75
        height = screen.height * 0.75
        x = (screen.width-width) * 0.5
        y = (screen.height-height)*0.5
    }


}
