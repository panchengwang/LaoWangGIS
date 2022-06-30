#include "laowangqml_plugin.h"
#include "MapControl.h"
#include <qqml.h>

void LaowangqmlPlugin::registerTypes(const char *uri)
{
    // @uri cn.pcgis
    qmlRegisterType<MapControl>(uri, 1, 0, "MapControl");
}

