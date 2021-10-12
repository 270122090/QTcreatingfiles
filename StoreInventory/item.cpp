
#include "item.h"
using namespace std;
#include <iostream>


Item::Item(QString item, int qty, QString path)
{
    itemname = item;
    quantity = qty;
    filepath= path;
}


void Item:: setitem(QString i)
{
    itemname = i;

}
void Item::setqty(int q)
{
    quantity = q;

}
void Item::setimage(QString p)
{
    filepath = p;
}

QString Item::getitem() const
{
    return itemname;
}
int Item::getqty() const
{
    return quantity;
}
QString Item::getimage()const
{
return filepath;
}
