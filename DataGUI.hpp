/// DataGUI.hpp


#ifndef DATAGUI_HPP
#define DATAGUI_HPP

#include <QMainWindow>

class QAction;
class QStandardItem;
class QModelIndex;
class QTreeView;
class QWidget;

namespace Utilities {


class DataGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DataGUI(QWidget *parent = 0);
    ~DataGUI();

    // Set/get XML tag that represents a datum
    QString GetDatumTag() const           { return datumTag; }
    void SetDatumTag()                    { datumTag = defaultDatumTag; }
    void SetDatumTag(const QString &dTag) { datumTag = dTag; }

private:
    static const char* const version;

    QString paramFilePath;
    QString configFilePath;
    QString servedApp, servedAppComment, servedAppVersion;

    QString datumTag;   // XML tag that identifies a datum
    static const QString defaultDatumTag;

private slots:
    void fileOpen();
    void fileRefresh();
    bool fileSave();
    bool fileSaveAs();
    bool fileClose();
    void about();
    void aboutQt();

private:
    void createModelAndView();
    void createActions();
    void createMenus();
    void createConnections();

private:
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileCloseAction;
    QAction *fileQuitAction;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QTreeView *treeParamView;

};


} // Utilities

#endif // DATAGUI_HPP
