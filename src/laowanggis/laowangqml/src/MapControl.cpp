#include "MapControl.h"

MapControl::MapControl(QQuickItem *parent)
    : QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    //     setFlag(ItemHasContents, true);
}




MapControl::~MapControl()
{
}




QSGNode *MapControl::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
{
    return NULL;
}
