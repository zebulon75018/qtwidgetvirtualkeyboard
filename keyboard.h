#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QString>
class key;

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    Keyboard(QWidget *p);

    signals:
    void keyPressed( QString t);
    void backspacePressed(  );
    void returnPressed(  );

private :
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent * E);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *);

    void initTooltip();
    void initKeys( int indexArraykeys,const char *keymap[]);
    key *findKey(QPoint p);
    void setKeyPressed( key *k,QPoint );

    QVector<QVector< key * > > keys;
    QLabel *tooltip;
    key *currentKey;
    int currentindexkeyboard;
    bool uppercase ;
};

#endif // KEYBOARD_H
