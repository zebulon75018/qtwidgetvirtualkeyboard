#include <QDebug>
#include "key.h"


key::key(QString t,QObject *parent) : QObject(parent)
{
  text = t;
  X =10;
  Y =10;
  W =t.length()*5 + 20;
  H =25;
  pressed = false;
}

QRect key::getRect()
{
    return QRect(X,Y,W,H);
}

void key::setX(int x )
{
  //  qDebug() << "setX " << x << " " << text;
  X = x;
}


void key::setY(int y )
{
  //  qDebug() << "setY " << y;
  Y = y;
}


void key::setIconFile(QString i )
{
  iconFilename = i;
  W = 25;
}

void key::setPressed( bool b)
{
//   qDebug() << "setPessed " << b;
   pressed = b;
}

void key::draw(QPainter *p,QStyle *style) {

    QStyleOptionButton opt;
    opt.palette = QPalette(Qt::red);
    /*
    if ( pressed )
           {
               opt.state = QStyle::State_Active;
           } else {
                opt.state = QStyle::State_Enabled;
           }
           */
    opt.rect = QRect(X, Y, W, H);

    if ( iconFilename !="" )
    {
        opt.icon = QIcon(iconFilename);
        opt.iconSize=QSize(16,16);
    }
    else
    {
        if (text =="&")  opt.text = "&&";
        else opt.text = text;
    }
    style->drawControl(QStyle::CE_PushButton, &opt, p);

}
