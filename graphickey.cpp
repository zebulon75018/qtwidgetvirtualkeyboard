#include <QPainter>
#include "graphickey.h"


GraphicKey::GraphicKey() : QGraphicsItem()
{

}

QRectF GraphicKey::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void GraphicKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-15, -15, 30, 30);
}


void GraphicKey::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   qDebug() << " Press";
}

void GraphicKey::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug() << " Move";
}

void GraphicKey::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug() << " Release";
}
