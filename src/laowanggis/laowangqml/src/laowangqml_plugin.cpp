#include "laowangqml_plugin.h"
#include "LWMapControl.h"
#include "LWFile.h"
#include "LWSQLConnection.h"
#include <qqml.h>

void LaowangqmlPlugin::registerTypes(const char *uri)
{
    // @uri cn.pcgis
    qmlRegisterType<LWMapControl>(uri, 1, 0, "LWMapControl");
    qmlRegisterType<LWFile>(uri, 1, 0, "LWFile");
    qmlRegisterType<LWSQLConnection>(uri, 1, 0, "LWSQLConnection");
}

