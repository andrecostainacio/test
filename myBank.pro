#-------------------------------------------------
#
# Project created by QtCreator 2015-05-29T18:27:04
#
#-------------------------------------------------

QT       += core
QT       += sql

QT       -= gui

TARGET = myBank
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    bank.cpp \
    client.cpp \
    account.cpp

HEADERS += \
    bank.h \
    client.h \
    account.h
