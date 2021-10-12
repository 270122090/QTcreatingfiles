#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include "item.h"

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemDialog(Item*& newItem, QWidget *parent = nullptr);
    ~AddItemDialog();

    void confirmAdd();
    void loadItemImage();

private:
    Ui::AddItemDialog *ui;
    Item** newitem;
    QString filepath;

};

#endif // ADDITEMDIALOG_H
