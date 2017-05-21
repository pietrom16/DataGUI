/// JsonTree.cpp

#include "JsonTree.hpp"
#include "TreeItem.hpp"
#include <QFile>

namespace GuiUtilities {



JsonTree::JsonTree(QObject *parent) :
    QAbstractItemModel(parent)
{
	mRootItem = new TreeItem;
    mHeaders.append("Key");
    mHeaders.append("Value");
}

bool JsonTree::Load(const QString &fileName)
{
    QFile file(fileName);
    bool success = false;
    if (file.open(QIODevice::ReadOnly)) {
        success = Load(&file);
        file.close();
    }
    else success = false;

    return success;
}

bool JsonTree::Load(QIODevice *device)
{
    return LoadJson(device->readAll());
}

bool JsonTree::LoadJson(const QByteArray &json)
{
    mDocument = QJsonDocument::fromJson(json);

    if (!mDocument.isNull())
    {
        beginResetModel();
        if (mDocument.isArray()) {
			mRootItem = TreeItem::Load(QJsonValue(mDocument.array()));
        } else {
			mRootItem = TreeItem::Load(QJsonValue(mDocument.object()));
        }
        endResetModel();
        return true;
    }

    return false;	// cannot load json file
}


QVariant JsonTree::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

	TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole) {

        if (index.column() == 0)
            return item->Tag();

        if (index.column() == 1)
            return item->Val();
    }

    return QVariant();
}

QVariant JsonTree::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {

        return mHeaders.value(section);
    }
    else
        return QVariant();
}

QModelIndex JsonTree::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

	TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
		parentItem = static_cast<TreeItem*>(parent.internalPointer());

	TreeItem *childItem = parentItem->Child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex JsonTree::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

	TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
	TreeItem *parentItem = childItem->Parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int JsonTree::rowCount(const QModelIndex &parent) const
{
	TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
		parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->ChildCount();
}

int JsonTree::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}


} // GuiUtilities
