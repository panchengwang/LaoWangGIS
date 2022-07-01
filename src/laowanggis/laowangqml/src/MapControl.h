#ifndef LAOWANG_PLUGIN_H
#define LAOWANG_PLUGIN_H

#include <QQuickItem>
#include <QQuickPaintedItem>

class MapControl : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MapControl)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit MapControl(QQuickItem *parent = nullptr);
    ~MapControl() override;

    void paint(QPainter *painter);

    Q_INVOKABLE QColor backgroundColor() const;
    Q_INVOKABLE void setBackgroundColor(const QColor& color);

signals:
    void backgroundColorChanged();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    //    QSGNode *updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatePaintNodeData);
    QColor _backgroundColor;
};

#endif // LAOWANG_PLUGIN_H
