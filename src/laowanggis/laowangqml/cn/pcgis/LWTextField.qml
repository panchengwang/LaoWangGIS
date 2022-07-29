import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

//Rectangle {

//    property alias text: input.text
//    border.width: 1
//    border.color: input.focus ? LWStyle.primary : LWStyle.dark
//    implicitHeight: LWStyle.input_height
//    clip: true
//    radius: LWStyle.radius
TextField {
    id: input
    //        anchors.margins: 3
    anchors.fill: parent
    text:""
    color: LWStyle.dark
    verticalAlignment: Text.AlignVCenter
    font.pointSize: LWStyle.input_font_point_size
    selectByMouse: true
    background: Rectangle{
        border.width: 1
        border.color: input.focus ? LWStyle.primary : LWStyle.dark
        implicitHeight: LWStyle.input_height
        clip: true
        radius: LWStyle.radius
    }

}

//}
