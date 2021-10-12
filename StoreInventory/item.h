#ifndef ITEM_H
#define ITEM_H

#include <QString>



class Item
{

private:

    QString itemname;
    int quantity;
    QString filepath;


public:
    Item(QString item, int qty, QString path);

    void setitem(QString i);
    void setqty(int q);
    void setimage(QString p);

    QString getitem() const;
    int getqty() const;
    QString getimage()const;


};

#endif // ITEM_H
