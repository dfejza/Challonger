#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T14:27:52
#
#-------------------------------------------------

QT += core gui widgets network concurrent sql

CONFIG += staticlib c++11

LIBS += -L"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib" -lUser32 -lKernel32

win32-g++* {
  QMAKE_CXXFLAGS += -Wall -Wextra -Wnon-virtual-dtor -pedantic -std=c++11
}
win32-msvc* {
  QMAKE_CXXFLAGS_WARN_ON -= -W3
  QMAKE_CXXFLAGS_WARN_ON += -W4 -w44640
  QMAKE_CXXFLAGS_RELEASE += -O2 -MD
  QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG /MAP /OPT:REF
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Challonger
TEMPLATE = app


SOURCES += src\main.cpp\
        src\mainwindow.cpp\
        src\PlayerFrame.cpp\

HEADERS  += src\mainwindow.h\
        src\PlayerFrame.h\

include(lib/anilist/AniListAPI.pri)
