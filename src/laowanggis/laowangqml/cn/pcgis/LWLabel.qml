import QtQuick 2.15
import QtQuick.Layouts 1.15


Text {
    id: button

    property alias label: button.text
    color: LWStyle.label_color
    font.pointSize: LWStyle.label_font_point_size

}
