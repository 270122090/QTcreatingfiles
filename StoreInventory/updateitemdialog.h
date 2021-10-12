#ifndef UPDATEITEMDIALOG_H
#define UPDATEITEMDIALOG_H
#include "item.h"

#include <QDialog>

namespace Ui {
class UpdateItemDialog;
}

class UpdateItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateItemDialog(Item* theItem, QWidget *parent = nullptr);
    ~UpdateItemDialog();

    void confirm();
    void newload();


private:
    Ui::UpdateItemDialog *ui;
    Item* theItem;
    QString filepath;
};

#endif // UPDATEITEMDIALOG_H
