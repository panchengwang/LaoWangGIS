#include "MapControl.h"
#include <QPainter>

MapControl::MapControl(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    //     setFlag(ItemHasContents, true);

    setAcceptedMouseButtons(Qt::AllButtons);
    _backgroundColor = QColor(255,255,255,0);
}




MapControl::~MapControl()
{
}

void MapControl::paint(QPainter *painter)
{
    QRect rect(0,0,width(),height());
    painter->fillRect(rect,_backgroundColor);
}

QColor MapControl::backgroundColor() const
{
    return _backgroundColor;
}

void MapControl::setBackgroundColor(const QColor& color)
{
    _backgroundColor = color;
    update();
    emit backgroundColorChanged();
}

void MapControl::keyPressEvent(QKeyEvent *event)
{
    QQuickPaintedItem::keyPressEvent(event);
}

void MapControl::keyReleaseEvent(QKeyEvent *event)
{
    QQuickPaintedItem::keyReleaseEvent(event);
}

void MapControl::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mouseDoubleClickEvent(event);
}

void MapControl::mouseMoveEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mouseMoveEvent(event);
}

void MapControl::mousePressEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mousePressEvent(event);
    qInfo() << event->pos();
}

void MapControl::mouseReleaseEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mouseReleaseEvent(event);
}




//QSGNode *MapControl::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
//{
//    return NULL;
//}
