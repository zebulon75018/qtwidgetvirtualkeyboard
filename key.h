#ifndef KEY_H
#define KEY_H

#include <QObject>
#include <QString>
#include <QIcon>
#include <QPainter>
#include <QStyleOptionButton>
#include <QStyle>


class key : public QObject
{
    Q_OBJECT
public:
    explicit key(QString t,QObject *parent = 0);

    void setX(int  );
    void setY(int  );
    void setIconFile(QString );
    void setPressed( bool b);

    void draw(QPainter *painter,QStyle *s);
    QRect getRect();

signals:

public slots:

public :
    int X;
    int Y;
    int W;
    int H;
    QString text;
    QString iconFilename;
    bool pressed;
};

#endif // KEY_H
