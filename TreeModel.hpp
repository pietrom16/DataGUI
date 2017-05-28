/// TreeModel.hpp

#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP

#include <QAbstractItemModel>
#include <QJsonDocument>
#include <QModelIndex>
#include <QVariant>

class QIODevice;

namespace GuiUtilities {

class TreeItem;


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QStringList &headers, const QString &data,
              QObject *parent = 0);
    TreeModel(QObject *parent = 0);
    ~TreeModel();

	// Getters

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

	// Setters

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;

public:
    bool Load(const QString &_fileName);
    bool Load(QIODevice *_device);
    bool LoadJson(const QByteArray &_json);

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem      *rootItem;
    QJsonDocument  document;
    //+D? QStringList    headers;
};


} // GuiUtilities

#endif // TREEMODEL_HPP
