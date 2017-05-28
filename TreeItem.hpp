/// TreeItem.hpp

#ifndef TREEITEM_HPP
#define TREEITEM_HPP

#include <QJsonValue>
#include <QList>
#include <QVariant>
#include <QVector>

namespace GuiUtilities {

typedef QVector<QVariant> ItemData;        // item with multiple columns: {tag, value, min, max, comment}

/**
 * A container of data items supplied by the tree model.
 */

class TreeItem
{
public:
	explicit TreeItem(TreeItem *_parent = 0);
	explicit TreeItem(const ItemData &_data, TreeItem *_parent = 0);
    ~TreeItem();

    // Getters

    QVariant  Data(int _col)  const { return itemData.value(_col); }
    QVariant  Tag()           const { return itemData[0];      }
    QVariant  Val()           const { return itemData[1];      }
    int       ColumnCount()   const { return itemData.count(); }

    TreeItem* Child(int _row) const { return childItems.value(_row); }
    int       ChildCount()    const { return childItems.count();     }
    int       ChildNumber()   const;    // id of this item relative to its parent

    TreeItem* Parent()        const { return parentItem; }

    // Setters

    bool SetData(int _col, const QVariant &_value);
    bool SetTag(const QVariant &_tag) { itemData[0] = _tag; return true; }
    bool SetVal(const QVariant &_val) { itemData[1] = _val; return true; }

    void AppendChild(TreeItem *_child) { childItems.append(_child); }
    bool RemoveChild(int _pos);
    bool InsertChildren(int _pos, int _count, int _columns);
    bool RemoveChildren(int _pos, int _count);

    bool InsertColumns(int _pos, int _columns);
    bool RemoveColumns(int _pos, int _columns);

    static TreeItem* Load(const QJsonValue& _value, TreeItem *_parent = 0); //+TODO & rename

private:
    ItemData           itemData;        // item with multiple columns: {tag, value, range, comment}
    TreeItem          *parentItem;
    QList<TreeItem*>   childItems;
};


} // GuiUtilities

#endif // TREEITEM_HPP
