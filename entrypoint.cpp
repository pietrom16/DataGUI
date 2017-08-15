/// entrypoint.cpp


/*
	Copyright (C) 2013-2017 Pietro Mele.
*/

#include "DataGUI.hpp"
#include "DevUtils.h"
#include "progArgs.h"
#include <iostream>
#include <string>
#include <QApplication>

using namespace GuiUtilities;
using namespace Utilities;

static const int vers = 0, subvers = 0, subsubvers = 1;


int main(int argc, char *argv[])
{
	TRACE;

	/// --- Command line parameters

    ProgArgs            arguments;
    ProgArgs::Argument  arg;
	std::string         value;

	TRACE;

    // Add the set of possible parameters:
    arg.Set("--parameters", "-p", "Path of the XML parameters file");
    arguments.AddArg(arg);
    arg.Set("--config", "-c", "Path of the XML configuration file");
    arguments.AddArg(arg);
    arg.Set("--version", "-v", "Version information");
    arguments.AddArg(arg);
    arg.Set("--help", "-h", "Help");
    arguments.AddArg(arg);

    arguments.Parse(argc, argv);

    if(arguments.GetValue("--version")) {
        std::cout << argv[0] << " version " << vers << "."
                                            << subvers << "."
                                            << subsubvers
                                            << std::endl;
        exit(0);
    }

    if(arguments.GetValue("--help")) {
        std::cout << "HELP - TODO" << std::endl;   //+T+
        arguments.Help();
        exit(0);
    }

    //+log arguments.Print();

    QString xmlFileName, configFileName;

    if(arguments.GetValue("--parameters", value) >= 0)
        xmlFileName = value.c_str();

    if(arguments.GetValue("--config", value) >= 0)
        configFileName = value.c_str();


    /// --- Start GUI

	TRACE;

    QApplication app(argc, argv);

	TRACE;

	app.setApplicationName(app.translate("main", "DataGUI"));
    //+TODO app.setWindowIcon(QIcon(":/icon.png"));
    app.setOrganizationName("Pietro Mele");
    app.setOrganizationDomain("https://sites.google.com/site/pietrom16");
#ifdef Q_WS_MAC
    app.setCursorFlashTime(0);
#endif

	TRACE;

    DataGUI dataGui;
    dataGui.show();

    return app.exec();
}


//+TODO: add logger
//+TODO: add help
