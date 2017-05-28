/// TreeModel.cpp

#include "TreeItem.hpp"
#include "TreeModel.hpp"

#include <iostream>
#include <QtWidgets>

namespace GuiUtilities {


TreeModel::TreeModel(const QStringList &_headers, const QString &_data, QObject *_parent)
    : QAbstractItemModel(_parent)
{
    ItemData rootData;
    foreach(QString header, _headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(_data.split(QString("\n")), rootItem);
}


TreeModel::TreeModel(QObject *_parent)
    : QAbstractItemModel(_parent)
{
    ItemData rootData;
    rootData << "Tag" << "Value";

    rootItem = new TreeItem(rootData);
    //+TODO setupModelData(data.split(QString("\n")), rootItem);
}


TreeModel::~TreeModel()
{
    delete rootItem;
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return item->Tag();

        if (index.column() == 1)
            return item->Val();
    }

    return QVariant();
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.value(section);
    else
        return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->Child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->Parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->ChildCount();
}


int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->ColumnCount();
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}


bool TreeModel::Load(const QString &fileName)
{
    QFile file(fileName);
    bool  success = false;

    if(file.open(QIODevice::ReadOnly)) {
        success = Load(&file);
        file.close();
    }
    else
        success = false;

    return success;
}


bool TreeModel::Load(QIODevice *device)
{
    return LoadJson(device->readAll());
}


bool TreeModel::LoadJson(const QByteArray &json)
{
    QJsonParseError *status = 0;
    document = QJsonDocument::fromJson(json, status);

    if(status->error != QJsonParseError::NoError) {
        std::cerr << status->errorString().toStdString();
        QErrorMessage *errorMessageDialog = new QErrorMessage;
        //QLabel *errorLabel = new QLabel(status->errorString());  //+?
        errorMessageDialog->setAccessibleName("Error loading JSON file");  //+?
        errorMessageDialog->setAccessibleDescription(status->errorString());  //+?
    }

    if(!document.isNull())
    {
        beginResetModel();
        if(document.isArray()) {
            rootItem = TreeItem::Load(QJsonValue(document.array()));
        } else {
            rootItem = TreeItem::Load(QJsonValue(document.object()));
        }
        endResetModel();
        return true;
    }

    std::cerr << Q_FUNC_INFO << " Error: cannot load JSON file.";

    return false;
}


TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }

    return rootItem;
}


} // GuiUtilities
