#ifndef GRAPHICKEY_H
#define GRAPHICKEY_H

#include <QGraphicsItem>
#include <QDebug>

class GraphicKey : public QGraphicsItem
{
public:
    GraphicKey();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) ;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) ;

private:
    QColor color;
};

#endif // GRAPHICKEY_H
