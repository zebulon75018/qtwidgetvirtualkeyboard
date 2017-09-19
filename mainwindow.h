#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void oneKeyPressed(QString t);
    void returnPressed( );
    void backspacePressed( );
};

#endif // MAINWINDOW_H
