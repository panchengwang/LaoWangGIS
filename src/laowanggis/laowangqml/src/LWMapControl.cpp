#include "LWMapControl.h"
#include <QPainter>

LWMapControl::LWMapControl(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    //     setFlag(ItemHasContents, true);

    setAcceptedMouseButtons(Qt::AllButtons);
    _backgroundColor = QColor(255,255,255,0);
}




LWMapControl::~LWMapControl()
{
}

void LWMapControl::paint(QPainter *painter)
{
    QRect rect(0,0,width(),height());
    painter->fillRect(rect,_backgroundColor);
}

QColor LWMapControl::backgroundColor() const
{
    return _backgroundColor;
}

void LWMapControl::setBackgroundColor(const QColor& color)
{
    _backgroundColor = color;
    update();
    emit backgroundColorChanged();
}

void LWMapControl::keyPressEvent(QKeyEvent *event)
{
    QQuickPaintedItem::keyPressEvent(event);
}

void LWMapControl::keyReleaseEvent(QKeyEvent *event)
{
    QQuickPaintedItem::keyReleaseEvent(event);
}

void LWMapControl::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mouseDoubleClickEvent(event);
}

void LWMapControl::mouseMoveEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mouseMoveEvent(event);
}

void LWMapControl::mousePressEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mousePressEvent(event);
    qInfo() << event->pos();
}

void LWMapControl::mouseReleaseEvent(QMouseEvent *event)
{
    QQuickPaintedItem::mouseReleaseEvent(event);
}




//QSGNode *MapControl::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData)
//{
//    return NULL;
//}
