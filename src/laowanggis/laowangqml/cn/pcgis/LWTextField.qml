import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15



Rectangle{
    id: control
    property alias echoMode : input.echoMode
    property alias text: input.text
    property string placeholderText: ''

    implicitHeight: LWStyle.input_height
    radius: LWStyle.radius
    border.width: 1
    border.color: input.focus ? LWStyle.primary : LWStyle.dark
    clip: true

    Text{
        id: placeHolder
        anchors.fill: parent
        anchors.margins: LWStyle.margin
        text: input.text.trim() == '' ? control.placeholderText : ''
        verticalAlignment: Text.AlignVCenter
        font.pointSize: LWStyle.input_font_point_size
        color: LWStyle.gray
    }

    TextInput{
        id : input
        anchors.fill: parent
        anchors.margins: LWStyle.margin
        verticalAlignment: Text.AlignVCenter
        selectByMouse: true
        font.pointSize: LWStyle.input_font_point_size
    }
}

//TextField {
//    id: input
//    text:""
//    color: LWStyle.dark
//    font.pointSize: LWStyle.input_font_point_size
//    selectByMouse: true
//    background: Rectangle{
//        border.width: 1
//        border.color: input.focus ? LWStyle.primary : LWStyle.dark
//        implicitHeight: LWStyle.input_height
//        radius: LWStyle.radius
//    }


//}


