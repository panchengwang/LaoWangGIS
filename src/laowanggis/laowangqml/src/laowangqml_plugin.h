#ifndef LAOWANGQML_PLUGIN_H
#define LAOWANGQML_PLUGIN_H

#include <QQmlExtensionPlugin>

class LaowangqmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // LAOWANGQML_PLUGIN_H
