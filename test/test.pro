QT -= core gui
CONFIG += c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
TARGET = gpio

INCLUDEPATH += \
    ../syntax
    
LIBS += \
    -L../syntax -lsyntax

HEADERS +=

SOURCES += \
    main.cpp
