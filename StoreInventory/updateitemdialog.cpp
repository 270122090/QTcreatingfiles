#include "updateitemdialog.h"
#include "ui_updateitemdialog.h"
#include <QMessageBox>
#include <QFileDialog>

UpdateItemDialog::UpdateItemDialog(Item* theItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateItemDialog)
{
    ui->setupUi(this);

    this->theItem = theItem;
    if (theItem!= nullptr)
    {
        ui->UName->setText(theItem->getitem());
        ui->UspinBox->setValue(theItem->getqty());
        QPixmap pixmap(theItem->getimage());
        ui->UImage->setPixmap(pixmap);
        ui->UImage->setScaledContents(true);
        filepath=theItem->getimage();
    }
    connect(ui->ULoadImage, &QPushButton::clicked, this,&UpdateItemDialog::confirm); // remember confirm is the function
    connect(ui->Updatebutton, &QPushButton::clicked, this,&UpdateItemDialog::newload);
}

UpdateItemDialog::~UpdateItemDialog()
{
    delete ui;
}

void UpdateItemDialog:: confirm()
{
    QString filename;

    filename=QFileDialog :: getOpenFileName(this, "Open Image", "./" ,"ImageFile(*.png *.jpg)"); // autofill in the file search container to only bring up png and jpg files

    if(filename!="") // "" means empty
    {
        int lastSlash = filename.lastIndexOf("/");
        QString shortname =filename.right(filename.size()-lastSlash-1);

        QFile::copy(filename, "./images/"+shortname);
        QPixmap pixmap("./images/"+shortname);

        ui->UImage->setPixmap(pixmap);
        ui->UImage->setScaledContents(true);

        filepath = "./images/" + shortname;
    }

}
void UpdateItemDialog::newload()
{

    int quantity = ui->UspinBox->value();

    if(quantity>=1)
    {
        theItem->setqty(quantity);
        theItem->setimage(filepath);
        this->close();
    }
    else
    {
        QMessageBox umb;
        umb.setText("Quantity must be greater than zero");
        umb.exec();

    }

}
