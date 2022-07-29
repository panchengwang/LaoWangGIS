pragma Singleton

import QtQuick 2.15

QtObject {

    // colors
    property string white     : "white"
    property string primary   : "#1976d2"
    property string secondary : "#26A69A"
    property string accent    : "#9C27B0"
    property string dark      : "#1d1d1d"
    property string dark_page : "#121212"
    property string positive  : "#21BA45"
    property string negative  : "#C10015"
    property string info      : "#31CCEC"
    property string warning   : "#F2C037"

    property int radius: 3
    property int padding: 5
    property int margin: 5
    property int spacing: 5

    //font
    property int font_point_size: 16

    // button
    property string button_text_color: LWStyle.white
    property string button_color: LWStyle.primary
    property int button_label_point_size: LWStyle.font_point_size
    property int button_icon_point_fize: button_label_point_size + 6
    property int button_margins: LWStyle.radius

    // header
    property int header_height: 40
    property string header_color: LWStyle.primary
    property int header_caption_point_size: 20
    property string header_caption_color: LWStyle.white

    // window header
    property int window_header_height: 32
    property string window_header_color: LWStyle.primary

    // label
    property int label_font_point_size: LWStyle.font_point_size
    property string label_color: LWStyle.dark

    // input
    property int input_height: 32
    property int input_font_point_size: LWStyle.font_point_size
    property int input_radius: LWStyle.radius
}
