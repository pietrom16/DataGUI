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


void DataGUI::fileOpen(){}
void DataGUI::contextMenuEvent(QContextMenuEvent *event)
{
    //+TODO
    /*
    QMenu menu(this);
    menu.addAction(fileOpenAction);
    menu.exec(event->globalPos());
    */
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
            "<p>Copyright 2013 Pietro Mele</p>"
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
    //+T+ add icons
    fileOpenAction = createAction("", tr("Open..."), this, QKeySequence::Open);
    fileSaveAction = createAction("", tr("Save"), this, QKeySequence::Save);
    fileSaveAsAction = createAction("", tr("Save As..."), this, QKeySequence::SaveAs);
    fileCloseAction = createAction("", tr("Close"), this, QKeySequence::Close);
    fileQuitAction = createAction("", tr("Quit"), this, QKeySequence::Quit);
/*
    fileOpenAction = createAction(":/fileopen.png", tr("Open..."),
            this, QKeySequence::Open);
    fileSaveAction = createAction(":/filesave.png", tr("Save"),
            this, QKeySequence::Save);
    fileSaveAsAction = createAction(":/filesave.png", tr("Save As..."),
            this, QKeySequence::SaveAs);
    fileCloseAction = createAction(":/fileclose.png", tr("Close"),
            this, QKeySequence::Close);
    fileQuitAction = createAction(":/filequit.png", tr("Quit"),
            this, QKeySequence::Quit);
*/
    //+D? fileQuitAction->setShortcuts(QKeySequence::Quit);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Copyright information"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}


void DataGUI::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    fileMenu->addAction(fileOpenAction);
    fileToolBar->addAction(fileOpenAction);
    fileMenu->addAction(fileSaveAction);
    fileToolBar->addAction(fileSaveAction);
    fileSaveAction->setEnabled(false);
    fileMenu->addAction(fileSaveAsAction);
    fileSaveAsAction->setEnabled(false);

    fileMenu->addSeparator();
    fileMenu->addAction(fileQuitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void DataGUI::createConnections(){}


} // Utilities
