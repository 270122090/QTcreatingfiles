#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemdialog.h"
#include "item.h"
#include "updateitemdialog.h"

#include <QFile>
#include <QTextStream>
#include <QListWidgetItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loaditem(); // show list straight away
    ui->MlistWidget->setCurrentRow(0);// also display the pictures on the first item
    handleitemlcick();


    connect(ui->actionAddItem, &QAction::triggered, this, &MainWindow:: handlemenuitemnew);
    connect(ui->RemoveBTN, &QPushButton::clicked, this, &MainWindow:: removeselected);

    connect(ui->MlistWidget, &QListWidget::itemClicked, this, &MainWindow:: handleitemlcick);// first declaring the ui impacted then what the action will be then
                                                                                                //the function that needs to happen NB handleitemclick is the function that
                                                                                               // is named in .h and coded below

    connect(ui->actionUpdateItem, &QAction::triggered, this, &MainWindow:: handlemenuupdateitem);

    connect(ui->actionExit, &QAction::triggered,this, &MainWindow::quitapp);

    connect(ui->actionLoad, &QAction::triggered,this, &MainWindow::loaditem);

    connect(ui->actionSave, &QAction::triggered,this, &MainWindow::readitem);

    connect(ui->btnsearch, &QPushButton::clicked,this, &MainWindow::searchItem);





}

MainWindow::~MainWindow()
{

    // free up the vector memory when main menu is closed.

    for (int i=0; i< productlist.size();i++ ) {
        delete productlist.at(i);
    }
    productlist.clear();

    delete ui;


}

//MlistWidget // this has no clicking involve

//actionAddItem // this is the menu bar on top left corner

 void MainWindow::handlemenuitemnew()
 {
    Item* newItem = nullptr;
    AddItemDialog addItemDialog(newItem, nullptr);
    addItemDialog.setModal(true);
    addItemDialog.exec();

    if(newItem != nullptr)
    {
        productlist.push_back(newItem);
        ui->MlistWidget->addItem(newItem->getitem());

    }
 }

    void MainWindow::removeselected()
    {
        int index = ui->MlistWidget->currentRow();
        if (index >=0)
        {
            // remove from vector
            Item* theItem = productlist.at(index);
            delete theItem;
            productlist.removeAt(index);

            //remove from listwidget

            delete ui->MlistWidget->currentItem();

        }

        ui->MNamelbl->setText(""); // this will remove the text and pictures as well
        ui->MQtylbl->setText("");
        QPixmap pixmap("none.png");
        ui->MImage->setPixmap(pixmap);
        ui->MImage->setScaledContents(true);



    }

    // data to display when clicked on the item in list
    void MainWindow::handleitemlcick()
    {
        int index = ui->MlistWidget->currentRow();
        if (index >=0)
            {
                Item* theItem = productlist.at(index);
                ui->MNamelbl->setText(theItem->getitem());
                ui->MQtylbl->setText(QString::number(theItem->getqty()));
                        QPixmap pixmap(theItem->getimage());
                ui->MImage->setPixmap(pixmap);
                ui->MImage->setScaledContents(true);
            }

    }

void MainWindow::handlemenuupdateitem()
{
    int index =ui->MlistWidget->currentRow();
    if (index >=0)
        {
            Item* theItem =productlist.at(index);
            if (theItem !=nullptr)
                {
                    UpdateItemDialog updateitemdialog(theItem, nullptr);// this
                    updateitemdialog.exec();

                    //update ui

                    ui->MNamelbl->setText(theItem->getitem());//this is for the main window so that
                    ui->MQtylbl->setText(QString:: number(theItem->getqty()));
                    QPixmap pixmap(theItem->getimage());
                    ui->MImage->setPixmap(pixmap);
                    ui->MImage->setScaledContents(true);
                }

        }
}

void MainWindow::quitapp()
{
    QApplication::quit();


}


void MainWindow::readitem() // write to file
{
    QFile outputFile("products.txt");

    outputFile.open(QIODevice::WriteOnly | QIODevice::Text); // this will be overiding

    QTextStream out(&outputFile);

    for (int i=0; i< productlist.size();i++ )
    {
        out << productlist.at(i)->getitem()<< ",";
        out << productlist.at(i)->getqty()<< ",";
        out << productlist.at(i)->getimage()<< endl;
    }

    out.flush();
    outputFile.close();

}

void MainWindow::loaditem()//
{
    QFile inputFile("products.txt");

    inputFile.open(QIODevice::ReadOnly | QIODevice::Text); // this will be overiding

    QTextStream in(&inputFile);

   // clear list widget and product vector

    //clear list widget

    ui->MlistWidget->clear();

    for (int i=0; i< productlist.size();i++)
    {
        delete productlist.at(i);
    }

    productlist.clear(); // emty current list so that things are not all loaded onto the list again.


    // read file

    while (!in.atEnd())
    {
        QString line=in.readLine(); // processing for one line until (!in.atEnd()) --> file ends
        QStringList info = line.split(","); // must include so to where info is personal name. telling compiler that the comma is refering to the same item and
                                            //to split when comma is no longer seen.

        // Add the product name to my list widget UI
        ui->MlistWidget->addItem(info.at(0));

        //handle the proudcut list vector

       Item* temp = new Item(info.at(0), info.at(1).toInt(),info.at(2));

       productlist.push_back(temp);

   }
    in.flush();
    inputFile.close();
}


// search feature


void MainWindow::searchItem()
{


// searching in a list
QString search = ui->txtSearch-> text();
    if (search =="")
    {
        for(int i = 0; i < ui->MlistWidget->count(); i++)
        {
            QListWidgetItem * temp =ui-> MlistWidget->item(i);
            temp->setBackground(Qt::white);
        }

    }
    else
    {
        QList<QListWidgetItem *> list = ui->MlistWidget->findItems(search, Qt::MatchContains);
        for(int i = 0; i < list.count(); ++i)
        {
            QListWidgetItem * temp = list.at(i);
            temp->setBackground(Qt::blue);
    }
 }
}



