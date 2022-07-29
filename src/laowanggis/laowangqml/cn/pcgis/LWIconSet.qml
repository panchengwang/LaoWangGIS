pragma Singleton

import QtQuick 2.15

QtObject {

    function getIcon(icon){
        var arr = icon.split('_')
        var typestr = arr[0]
        var text = arr[1]
        return text ? text : ''
    }

    function getFontName(icon){
        var arr = icon.split('_')
        var typestr = arr[0]
        var text = arr[1]
        if(typestr === 'materialoutlined'){
            return materialOutlinedFont.name
        }

        return ''
    }


    property FontLoader materialOutlinedFont: FontLoader{
        source: "./fonts/MaterialIconsOutlined-Regular.otf"
    }


    property string icon_material_outlined_search: "materialoutlined_\ue8b6"
    property string icon_material_outlined_home: "materialoutlined_\ue88a"
    property string icon_material_outlined_account_circle: "materialoutlined_\ue853"
    property string icon_material_outlined_settings: "materialoutlined_\ue8b8"
    property string icon_material_outlined_done: "materialoutlined_\ue876"
    property string icon_material_outlined_info: "materialoutlined_\ue88e"
    property string icon_material_outlined_check_circle: "materialoutlined_\ue86c"
    property string icon_material_outlined_delete: "materialoutlined_\ue872"
    property string icon_material_outlined_visibility: "materialoutlined_\ue8f4"
    property string icon_material_outlined_shopping_cart: "materialoutlined_\ue8cc"
    property string icon_material_outlined_logout: "materialoutlined_\ue9ba"
    property string icon_material_outlined_apps: "materialoutlined_\ue5c3"
}
