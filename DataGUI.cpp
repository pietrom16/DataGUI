/// DataGUI.cpp


#include "DataGUI.hpp"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QTreeView>


namespace {

QAction *createAction(const QString &icon, const QString &text,
        QObject *parent,
        const QKeySequence &shortcut=QKeySequence())
{
    QAction *action = new QAction(QIcon(icon), text, parent);
    if (!shortcut.isEmpty())
        action->setShortcut(shortcut);
    return action;
}

} // anonymous namespace


namespace Utilities {


const char* const DataGUI::version = "0.0.3";

const QString DataGUI::defaultDatumTag = "param";


DataGUI::DataGUI(QWidget *parent)
    :
      QMainWindow(parent),
      treeParamView(0)
{
    SetDatumTag();

    servedApp = "Not connected";
    servedAppComment = "-";
    servedAppVersion = "-";

    paramFilePath = ".";

    createModelAndView();
    createActions();
    createMenus();
    createConnections();

    statusBar()->showMessage(tr("Ready"));

    QString title = servedApp + " - " + QApplication::applicationName();
    setWindowTitle(tr(title.toLatin1().data()));

//+    setWindowTitle(tr("%1 [*]").arg(QApplication::applicationName()));

    setMinimumSize(160, 160);
    resize(480, 320);
}


DataGUI::~DataGUI()
{}


void DataGUI::contextMenuEvent(QContextMenuEvent *event)
{
    //+TODO
    /*
    QMenu menu(this);
    menu.addAction(fileOpenAction);
    menu.exec(event->globalPos());
    */
}


//+TODO
int DataGUI::databaseConnect(){}
int DataGUI::serverConnect(){}
int DataGUI::pause(){}
int DataGUI::reload(){}
int DataGUI::search(){}
int DataGUI::settings(){}
int DataGUI::info(){}
int DataGUI::terminateServer(){}


int DataGUI::quitGui()
{
	//+TODO - Ask whether to save
	exit(0);
}


void DataGUI::about()
{
    QString title = servedApp + " - " + "DataGUI";

    QString message =
            "<p><b>" + servedApp + "</b> vers. " + servedAppVersion + " - " + servedAppComment + "</p>"
            "<p><b>DataGUI</b> vers. " + version + " - A GUI to view and modify data of a core application.</p>"
	        "<p>Copyright (C) 2013-2017 Pietro Mele</p>"
            ;

    QMessageBox::about(this,
                       tr(title.toLatin1().data()),
                       tr(message.toLatin1().data()));
}


void DataGUI::aboutQt()
{}


void DataGUI::createModelAndView(){}


void DataGUI::createActions()
{
	databaseConnectAct = createAction(":/images/database-1.svg", tr("Database"), this);
	databaseConnectAct->setStatusTip(tr("Connect to database"));
	serverConnectAct = createAction(":/images/server-1.svg", tr("Server"), this);
	serverConnectAct->setStatusTip(tr("Connect to application server"));
	pauseAct = createAction(":/images/pause-1.svg", tr("&Pause"), this);
	pauseAct->setStatusTip(tr("Pause updates"));
	reloadAct = createAction(":/images/reload.svg", tr("&Reload"), this);
	reloadAct->setStatusTip(tr("Reload data"));
	searchAct = createAction(":/images/search-1.svg", tr("&Search"), this);
	searchAct->setStatusTip(tr("Search for variables"));
	settingsAct = createAction(":/images/settings-5.svg", tr("Settings"), this);
	settingsAct->setStatusTip(tr("GUI settings"));
	infoAct = createAction(":/images/info.svg", tr("&Info"), this);
	infoAct->setStatusTip(tr("Information"));
	terminateServerAct = createAction(":/images/exit.svg", tr("Quit server"), this);
	terminateServerAct->setStatusTip(tr("Terminate the server. The GUI will keep running"));
	quitGuiAct = createAction(":/images/exit.svg", tr("&Quit GUI"), this, QKeySequence::Quit);
	quitGuiAct->setStatusTip(tr("Exit the GUI only. The server will keep running"));
	aboutAct = new QAction(tr("About"), this);
    aboutAct->setStatusTip(tr("Copyright information"));
}


void DataGUI::createMenus()
{
	QMenu *connectionMenu = menuBar()->addMenu(tr("Connection"));
	QToolBar *toolBar = addToolBar(tr("Connection"));

	connectionMenu->addAction(serverConnectAct);
	connectionMenu->addSeparator();
	connectionMenu->addAction(pauseAct);
	toolBar->addAction(pauseAct);
	//fileSaveAction->setEnabled(false);
	connectionMenu->addAction(reloadAct);
	toolBar->addAction(reloadAct);
	connectionMenu->addSeparator();
	connectionMenu->addAction(searchAct);
	connectionMenu->addAction(settingsAct);
	connectionMenu->addAction(infoAct);
	connectionMenu->addSeparator();
	connectionMenu->addAction(terminateServerAct);
	connectionMenu->addAction(quitGuiAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
	aboutQtAct = helpMenu->addAction(tr("About Qt"), qApp, &QApplication::aboutQt);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void DataGUI::createConnections()
{
	connect(databaseConnectAct, &QAction::triggered, this, &DataGUI::databaseConnect);
	connect(serverConnectAct, &QAction::triggered, this, &DataGUI::serverConnect);
	connect(pauseAct, &QAction::triggered, this, &DataGUI::pause);
	connect(reloadAct, &QAction::triggered, this, &DataGUI::reload);
	connect(searchAct, &QAction::triggered, this, &DataGUI::search);
	connect(settingsAct, &QAction::triggered, this, &DataGUI::settings);
	connect(infoAct, &QAction::triggered, this, &DataGUI::info);
	connect(terminateServerAct, &QAction::triggered, this, &DataGUI::terminateServer);
	connect(quitGuiAct, &QAction::triggered, this, &DataGUI::quitGui);
	connect(aboutAct, &QAction::triggered, this, &DataGUI::about);
}


} // Utilities
