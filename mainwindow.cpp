#include <QLabel>

#include "mainwindow.h"
#include "graphickey.h"
#include "keyboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Keyboard *k = new Keyboard(0x0);
    this->setCentralWidget(k);
    connect(k, SIGNAL(keyPressed(QString)), this, SLOT(oneKeyPressed(QString)));
    connect(k, SIGNAL(backspacePressed()), this, SLOT(backspacePressed()));
    connect(k, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

}

MainWindow::~MainWindow()
{
}
\

void MainWindow::oneKeyPressed(QString t)
{
    qDebug() << " keyPressed " << t;
}
void MainWindow::returnPressed( )
{
    qDebug() << " return ";
}

void MainWindow::backspacePressed( )
{
    qDebug() << " backspace ";
}
