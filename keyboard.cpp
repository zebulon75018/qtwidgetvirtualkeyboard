#include <QPainter>
#include <QMouseEvent>
#include<QDebug>
#include "key.h"
#include "keyboard.h"

#define KEYS_TYPE 4

// TODO make an enum
#define LOWERCASE 0
#define NUMBER 1
#define UPPERCASE 2
#define PUNCTUATION 3

// Declaration off the differente keys...


const char *en_lower_keymap[] = {
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
    "a", "s", "d", "f", "g", "h", "j", "k", "l",";",
    "Caps", "z", "x", "c", "v", "b", "n", "m",",", "backspace",
    "123", ".", "space", "@", "return",
};

const char *en_upper_keymap[] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "A", "S", "D", "F", "G", "H", "J", "K", "L",";",
    "Caps", "Z", "X", "C", "V", "B", "N", "M",",", "backspace",
    "123", ".", "space", "@", "return",
};

const char *en_number_keymap[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "/", ":", ";", "(", ")", "€", "&", "@", "\"",
    "#+=", ".", ",", "?", "!", "'", "+","\\","%","backspace",
    "ABC", ",", "space", ".", "return",
};

const char *en_punctuation_keymap[] = {
    "[", "]", "{", "}", "#", "%", "^", "*", "+", "=",
    "_", "\\", "|", "~", "<", ">", "=","$", "@", "\"",
    "123", ".", ",", "?", "!", "'","/",":",";", "backspace",
    "ABC", ",", "space", ".", "return",
};

// In witch row are the key... (there's 4 rows )
const int row_keymapp[] = {
    0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3
};

const int nbkey = sizeof(en_lower_keymap)/ sizeof(char *);

Keyboard::Keyboard(QWidget *p) : QWidget(p)
{
    currentKey = 0x0;
    currentindexkeyboard = LOWERCASE;
    uppercase = false;

    initTooltip();

    keys = QVector<QVector< key * > >(KEYS_TYPE);
    for (int n=0;n < KEYS_TYPE ; n++)
    {
      keys[n] = QVector< key * >(nbkey);
    }

    initKeys(LOWERCASE,en_lower_keymap);
    initKeys(NUMBER,en_number_keymap);
    initKeys(UPPERCASE,en_upper_keymap);
     initKeys(PUNCTUATION,en_punctuation_keymap);
}

void Keyboard::initKeys( int indexArraykeys,const char *keymap[])
{
    int row = 0;
    for(int n=0; n< nbkey; n++)
    {
        keys[indexArraykeys][n] = new key(keymap[n]);
        if ( n>0)
        {
            if (keymap[n] == "return" )     keys[indexArraykeys][n]->setIconFile(":/img/img/enter.png");
            if (keymap[n] == "backspace" )  keys[indexArraykeys][n]->setIconFile(":/img/img/backspace.jpg");
            if (keymap[n] == "Caps" )       keys[indexArraykeys][n]->setIconFile(":/img/img/caps.png");
            if (keymap[n] == "space" )      keys[indexArraykeys][n]->W=130;

            if (row_keymapp[n-1]!=row_keymapp[n])
            {
                row ++;
                keys[indexArraykeys][n]->setX(0); //offetrows[row]);
            } else {
                keys[indexArraykeys][n]->setX(keys[indexArraykeys][n-1]->X + keys[indexArraykeys][n-1]->W);
            }
            keys[indexArraykeys][n]->setY(row_keymapp[n]*25);
        } else {
          //  keys[indexArraykeys][n]->setX(offetrows[0]);
            keys[indexArraykeys][n]->setX(0);
            keys[indexArraykeys][n]->setY(row_keymapp[n]*25);
        }
    }
}

void Keyboard::initTooltip()
{
    tooltip = new QLabel("");
    tooltip->setWindowFlags(Qt::WindowDoesNotAcceptFocus | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::BypassWindowManagerHint);
    QFont serifFont("Times", 18, QFont::Bold);
    tooltip->setFont(serifFont);
    tooltip->setAlignment(Qt::AlignCenter);

}

void Keyboard::mousePressEvent(QMouseEvent * e) {
    QPoint pos = e->pos();
    setKeyPressed( findKey(pos), pos );
}

void Keyboard::mouseMoveEvent(QMouseEvent * e) {
    QPoint pos = e->pos();

    if (currentKey != 0x0 && !currentKey->getRect().contains(pos)) {
        tooltip->hide();
        currentKey->setPressed(false);
        this->repaint();
    }
    setKeyPressed( findKey(pos), pos );
 }

void Keyboard::mouseReleaseEvent(QMouseEvent *e) {
    QPoint pos = e->pos();
    tooltip->hide();
    key *k= findKey( pos );
    if (k != 0x0 )
    {
        if ( k->text == "ABC")
        {
            currentindexkeyboard = LOWERCASE;
            repaint();
            return;
        }
        if (k->text== "#+=" )
        {
            currentindexkeyboard = PUNCTUATION;
            repaint();
            return;
        }

        if (k->text=="Caps")
        {   if ( uppercase ==false)
            {
               currentindexkeyboard = UPPERCASE;
               uppercase = true;
            }
            else
            {
                currentindexkeyboard = LOWERCASE;
                uppercase = false;
            }
            repaint();
            return;
        }

        if (k->text=="123")
        {
            currentindexkeyboard = NUMBER;
            repaint();
        }
        else
        {
            if ( k->text =="backspace" )
            {
                emit backspacePressed();
                return;
            }

            if (k->text=="enter")
            {
                emit returnPressed();
                return;
            }
            if ( k->text == "space")
            {
                   emit keyPressed(" ");
            } else
            {
                emit keyPressed(k->text);
            }
        }
    }
}
key *Keyboard::findKey(QPoint p)
{
    foreach (key *k, keys[currentindexkeyboard])
    {
      if (k->getRect().contains(p))
      {
          return k;
      }
    }
    return 0x0;
}

void Keyboard::setKeyPressed( key *k, QPoint pos)
{
    currentKey = k;
    if (k == 0x0) return;

    k->setPressed(true);
    this->repaint();

    QPoint p = QWidget::mapToGlobal(this->pos() +QPoint( k->X, k->Y));
    tooltip->setGeometry(p.x(),p.y()-50,50, 50);
    tooltip->setText(k->text);
    tooltip->show();
}

void Keyboard::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    foreach (key *k, keys[currentindexkeyboard])
    {
        k->draw(&painter,style());
    }
}
