#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "game.h"
#include "readerandwriter.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Press_buttom_Test();
    void Press_buttom_MenuRecord();
    void Press_buttom_NewGame();

private:
    Ui::MainWindow *ui;

    Game game;

    QString ProcessingRecords(QString str);

};
#endif // MAINWINDOW_H
