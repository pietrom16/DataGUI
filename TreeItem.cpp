/// TreeItem.cpp

#include "TreeItem.hpp"
#include <QJsonArray>
#include <QJsonObject>


namespace GuiUtilities {


TreeItem::TreeItem(TreeItem *_parent)
	: parentItem(_parent)
{
}


TreeItem::TreeItem(const ItemData &_data, TreeItem *_parent)
    : itemData(_data), parentItem(_parent)
{
}


TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}


int TreeItem::ChildNumber() const
{
    if(parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}


bool TreeItem::SetData(int _col, const QVariant &_value)
{
    if (_col < 0 || _col >= itemData.size())
        return false;

    itemData[_col] = _value;

    return true;
}


bool TreeItem::RemoveChild(int _pos)
{
    if(_pos < 0 || _pos > childItems.size())
        return false;

    delete childItems.takeAt(_pos);

    return true;
}


bool TreeItem::InsertChildren(int _pos, int _count, int _columns)
{
    if(_pos < 0 || _pos > childItems.size())
        return false;

    for(int row = 0; row < _count; ++row)
    {
        ItemData data(_columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(_pos, item);
    }

    return true;
}


bool TreeItem::RemoveChildren(int _pos, int _count)
{
    if(_pos < 0 || _pos + _count > childItems.size())
        return false;

    for(int row = 0; row < _count; ++row)
        delete childItems.takeAt(_pos);

    return true;
}


bool TreeItem::InsertColumns(int _pos, int _columns)
{
    if(_pos < 0 || _pos > itemData.size())
        return false;

    for(int column = 0; column < _columns; ++column)
        itemData.insert(_pos, QVariant());

    foreach(TreeItem *child, childItems)
        child->InsertColumns(_pos, _columns);

    return true;
}


bool TreeItem::RemoveColumns(int _pos, int _columns)
{
    if (_pos < 0 || _pos + _columns > itemData.size())
        return false;

    for (int column = 0; column < _columns; ++column)
        itemData.remove(_pos);

    foreach (TreeItem *child, childItems)
        child->RemoveColumns(_pos, _columns);

    return true;
}


TreeItem* TreeItem::Load(const ItemData& _value, TreeItem* _parent)
{
    //+TODO
}


/*
TreeItem* TreeItem::Load(const QJsonValue& _value, TreeItem* _parent)
{
    TreeItem *rootItem = new TreeItem(_parent);
    rootItem->SetTag("root");

    if(_value.isObject())
    {
        // Get all _value childs
        for(QString key : _value.toObject().keys())
        {
            const QJsonValue v = _value.toObject().value(key);
            TreeItem *child = Load(v, rootItem);
            child->SetTag(key);
            child->SetType(v.type());
            rootItem->AppendChild(child);
        }
    }
    else if(_value.isArray())
    {
        // Get all _value childs
        int index = 0;
        for(QJsonValue v : _value.toArray())
        {
            TreeItem *child = Load(v, rootItem);
            child->SetTag(QString::number(index));
            child->SetType(v.type());
            rootItem->AppendChild(child);
            ++index;
        }
    }
    else
    {
        rootItem->SetValue(_value.toVariant().toString());
        rootItem->SetType(_value.type());
    }

    return rootItem;
}
*/

} // GuiUtilities
