#include "laowangqml_plugin.h"
#include "LWMapControl.h"
#include <qqml.h>

void LaowangqmlPlugin::registerTypes(const char *uri)
{
    // @uri cn.pcgis
    qmlRegisterType<LWMapControl>(uri, 1, 0, "LWMapControl");
}

