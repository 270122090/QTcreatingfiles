#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "item.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

void handlemenuitemnew();
void removeselected();
void handleitemlcick();

void handlemenuupdateitem();

void quitapp();

void readitem();

void loaditem();

void searchItem();


private:
    Ui::MainWindow *ui;
    QVector <Item*> productlist;// create a vector pointer to all theproducts i am going to hld datamodel

};
#endif // MAINWINDOW_H


