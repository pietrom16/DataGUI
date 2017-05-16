/// DataGUI.hpp


#ifndef DATAGUI_HPP
#define DATAGUI_HPP

#include <QIODevice>
#include <QMainWindow>

class QAction;
class QIcon;
class QJsonItem;
class QJsonModel;
class QModelIndex;
class QStandardItem;
class QTreeView;
class QWidget;

namespace GuiUtilities {

class TreeItem;
class TreeModel;


class DataGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DataGUI(QWidget *parent = 0);
    ~DataGUI();

    bool Load(const QString &fileName);
    bool Load(QIODevice *device);
    bool LoadJson(const QByteArray &json);

	int Test();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    static const char* const version;

    QString paramFilePath;
    QIODevice::OpenModeFlag openMode = QIODevice::ReadOnly; // ReadWrite
    QString configFilePath;
    QString servedApp, servedAppComment, servedAppVersion;

    int  refreshDelay = 1000;    // milliseconds
    bool modifiedData = false;

private slots:
	int databaseConnect();
	int serverConnect();
	int pause();
	int reload();
	int search();
	int settings();
	int info();
	int terminateServer();
	int quitGui();
	void about();
    void aboutQt();

private:
    void createModelAndView();
    void createActions();
    void createMenus();
    void createConnections();

private:
	QAction *databaseConnectAct;
	QAction *serverConnectAct;
	QAction *pauseAct;
	QAction *reloadAct;
	QAction *searchAct;
	QAction *settingsAct;
	QAction *infoAct;
	QAction *terminateServerAct;
	QAction *quitGuiAct;
	QAction *aboutAct;
    QAction *aboutQtAct;

private:
    QTreeView *treeParamView = 0;
    TreeModel *treeModel = 0;

    QIcon *serverIcon = 0;
};


} // GuiUtilities

#endif // DATAGUI_HPP
