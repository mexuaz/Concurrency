TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++17

LIBS += -lpthread


SOURCES += \
    SearchInsertDelete.cpp \
    sidlist.cpp

HEADERS += \
    sidlist.h
