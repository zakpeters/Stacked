#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T16:40:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Client
TEMPLATE = app
#linux: QT += x11extras

#osx stuff comment out if it causes problems
macx: QMAKE_CXXFLAGS += -std=c++11
macx: LIBS += -L"/usr/local/lib"
macx: LIBS += -L"$$PWD"
macx: INCLUDEPATH += "/usr/local/include"
macx: DEPENDPATH += "/usr/local/include"

#linux
#these will only work if you have the libraries installed to your system:)
linux: LIBS += -L"/usr/lib"
linux: LIBS += -L"/usr/local/lib"
linux: INCLUDEPATH += "/usr/local/include"
linux: INCLUDEPATH += "/usr/include/"
linux: DEPENDPATH += "/usr/local/include"
linux: DEPENDPATH += "/usr/include"
linux: INCLUDEPATH += "/usr/include/mysql/"

#windows
#windows
win32: INCLUDEPATH += "C:\\SFML\\include"
win32: DEPENDPATH += "C:\\SFML\\include"
win32: LIBS += -L"C:\\SFML\\lib"
win32: INCLUDEPATH += "C:\\mysql\\include"
win32: DEPENDPATH += "C:\\mysql\\include\\mysql"
win32: LIBS += -L"C:\\mysql\\lib"
win32: LIBS += -L"C:\\mysql\\lib\\mysql"


LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -lBox2D
#LIBS += -lBox2d
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

SOURCES += main.cpp\
    client.cpp \
    teachwin.cpp \
    studwin.cpp \
    loginwin.cpp \
    teachreg.cpp \
    studreg.cpp \
    datastructure.cpp \
    level.cpp \
    puzzle.cpp \
    usersocket.cpp \
    message.cpp \
    graphicsobject.cpp \
    graphicsobjecttest.cpp \
    arraypuzzle.cpp \
    listpuzzle.cpp \
    hashtablepuzzle.cpp \
    stackpuzzle.cpp \
    sprite2dobject.cpp \
    action.cpp \
    puzzlewindow.cpp \
    spritedefinition.cpp \
    binarytreepuzzle.cpp


HEADERS  += client.h \
    teachwin.h \
    studwin.h \
    loginwin.h \
    teachreg.h \
    studreg.h \
    datastructure.h \
    level.h \
    puzzle.h \
    usersocket.h \
    message.h \
    graphicsobject.h \
    graphicsobjecttest.h \
    exceptions.h \
    arraypuzzle.h \
    listpuzzle.h \
    hashtablepuzzle.h \
    stackpuzzle.h \
    sprite2dobject.h \
    action.h \
    puzzlewindow.h \
    spritedefinition.h \
    binarytreepuzzle.h
    exceptions.h
    #Box2D.h

FORMS    += client.ui \
    teachwin.ui \
    studwin.ui \
    loginwin.ui \
    teachreg.ui \
    studreg.ui

RESOURCES += \
    style.qrc \
    sprites.qrc

DISTFILES += \
    Stacked.pro.user


