#ifndef LAOWANG_PLUGIN_H
#define LAOWANG_PLUGIN_H

#include <QQuickItem>

class MapControl : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MapControl)

public:
    explicit MapControl(QQuickItem *parent = nullptr);
    ~MapControl() override;


protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData);
};

#endif // LAOWANG_PLUGIN_H
