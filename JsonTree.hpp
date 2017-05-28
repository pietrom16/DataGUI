/// JsonTree.hpp

#ifndef JSONTREE_HPP
#define JSONTREE_HPP

#include <QAbstractItemModel>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QIcon>

namespace GuiUtilities {

class TreeItem;

/** JsonTree
 *  Extension of a QTreeView to store JSON data.
 */

class JsonTree : public QAbstractItemModel
{
    Q_OBJECT
public:
	explicit JsonTree(QObject *parent = 0);
    bool Load(const QString& fileName);
    bool Load(QIODevice * device);
    bool LoadJson(const QByteArray& json);
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
	TreeItem     *mRootItem = 0;
    QJsonDocument mDocument;
	QStringList   mHeaders;
};


} // GuiUtilities

#endif // JSONTREE_HPP
