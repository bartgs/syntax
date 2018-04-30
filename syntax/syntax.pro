QT -= core gui
CONFIG += c++11

TEMPLATE = lib
TARGET = syntax

HEADERS += \
    Command.h \
    IValue.h \
    Option.h \
    Param.h \
    Syntax.h

SOURCES += \
    Command.cpp \
    Syntax.cpp
    

