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


void DataGUI::fileOpen()
{

}


void DataGUI::fileRefresh(){}


bool DataGUI::fileSave(){}


bool DataGUI::fileSaveAs(){}


bool DataGUI::fileClose(){}


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
//+	databaseConnectAct = createAction(":/database-1.svg", tr("Database"), this);
//+	databaseConnectAct->setStatusTip(tr("Connect to database"));
//+B	serverConnectAct = createAction(":/server-1.svg", tr("Server"), this);
//+B	serverConnectAct = createAction(":/server-1.png", tr("Server"), this);
	serverConnectAct = createAction("", tr("Server"), this);
	serverConnectAct->setStatusTip(tr("Connect to application server"));
/*	pauseAct = createAction(":/pause-1.svg", tr("&Pause"), this);
	pauseAct->setStatusTip(tr("Pause updates"));
	reloadAct = createAction(":/reload.svg", tr("&Reload"), this);
	reloadAct->setStatusTip(tr("Reload data"));
	searchAct = createAction(":/search-1.svg", tr("&Search"), this);
	searchAct->setStatusTip(tr("Search for variables"));
	settingsAct = createAction(":/settings-5.svg", tr("Settings"), this);
	settingsAct->setStatusTip(tr("GUI settings"));
	infoAct = createAction(":/info.svg", tr("&Info"), this);
	infoAct->setStatusTip(tr("Information"));
	terminateServerAct = createAction(":/exit.svg", tr("Quit server"), this);
	terminateServerAct->setStatusTip(tr("Terminate the server. The GUI will keep running"));
	quitGuiAct = createAction(":/exit.svg", tr("Quit GUI"), this, QKeySequence::Quit);
	quitGuiAct->setStatusTip(tr("Exit the GUI only. The server will keep running"));
*/	aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Copyright information"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}


void DataGUI::createMenus()
{
	QMenu *connectionMenu = menuBar()->addMenu(tr("Connection"));
	QToolBar *toolBar = addToolBar(tr("Connection"));

	connectionMenu->addAction(serverConnectAct);
	connectionMenu->addSeparator();
/*	connectionMenu->addAction(pauseAct);
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
*/
    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void DataGUI::createConnections(){}


} // Utilities
