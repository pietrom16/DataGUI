#-------------------------------------------------
#
# Project: DataGUI
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataGUI
TEMPLATE = app


SOURCES += \
	DataGUI.cpp \
	entrypoint.cpp \
	progArgs.cpp \
	TreeItem.cpp \
	JsonTree.cpp \
	TreeModel.cpp

HEADERS += \
	DataGUI.hpp \
	progArgs.h \
	TreeItem.hpp \
	JsonTree.hpp \
	TreeModel.hpp \
    DevUtils.h

OTHER_FILES += \
	TODO

RESOURCES += \
	DataGUI.qrc

DISTFILES += \
	LICENSE \
	README.md \
	gitignore \
	LICENSE_3rdParty \
    DataGUI.config
