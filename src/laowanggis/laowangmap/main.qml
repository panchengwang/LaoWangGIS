import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import cn.pcgis 1.0

LWApplicationWindow {
    id: app
    LWMapControl{
        anchors.fill: parent
        backgroundColor: "white"
        focus: true
    }
}
