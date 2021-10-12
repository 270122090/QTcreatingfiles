#include "additemdialog.h"
#include "ui_additemdialog.h"

#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

AddItemDialog::AddItemDialog(Item*& newItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
    this->newitem = &newItem;
    filepath="none.png";

    connect(ui->addbutton, &QPushButton::clicked, this,&AddItemDialog::confirmAdd);// connect is the 'to to slot'


    connect(ui->loadimage, &QPushButton::clicked, this,&AddItemDialog::loadItemImage);

    QDir pathDir("./images"); // declaring where my images is stored but
    if(!pathDir.exists()) //the folder doesn't exist
    {
        QDir().mkdir("./images"); // then create the folder
    }

}

AddItemDialog::~AddItemDialog()
{
    delete ui;

}


void AddItemDialog :: confirmAdd()
{
    QString productName = ui->txtName->text();//  new variables
    int quantity = ui->addspinBox->value();
    if(productName.trimmed() !="" &&quantity>=1)
    {
        *newitem = new Item(productName, quantity, filepath);// using new variables
        this->close();

    }
    else
    {
        QMessageBox addwarning;
        addwarning.setText("You must add a valid name & quantity");
        addwarning.exec();
    }


}

void AddItemDialog :: loadItemImage()
{
    QString filename;

    filename=QFileDialog :: getOpenFileName(this, "Open Image", "./" ,"ImageFile(*.png *.jpg)"); // autofill in the file search container to only bring up png and jpg files

    if(filename!="") // "" means empty
    {
        int lastSlash = filename.lastIndexOf("/");
        QString shortname =filename.right(filename.size()-lastSlash-1);

        QFile::copy(filename, "./images/"+shortname);
        QPixmap pixmap("./images/"+shortname);

        ui->AddImage->setPixmap(pixmap);
        ui->AddImage->setScaledContents(true);

        filepath = "./images/" + shortname;
    }

}
