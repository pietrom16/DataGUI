/// TreeModel.cpp

#include "TreeItem.hpp"
#include "TreeModel.hpp"

#include <iostream>
#include <QtWidgets>

namespace GuiUtilities {


TreeModel::TreeModel(const QStringList &_headers, const QString &_data, QObject *_parent)
    : QAbstractItemModel(_parent)
{
    QVector<QVariant> rootData;
    foreach(QString header, _headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(_data.split(QString("\n")), rootItem);
}


TreeModel::TreeModel(QObject *_parent)
    : QAbstractItemModel(_parent)
{
    QVector<QVariant> rootData;
    rootData << "Tag" << "Value";

    rootItem = new TreeItem(rootData);
    //+TODO setupModelData(data.split(QString("\n")), rootItem);
}


TreeModel::~TreeModel()
{
    delete rootItem;
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



} // GuiUtilities
