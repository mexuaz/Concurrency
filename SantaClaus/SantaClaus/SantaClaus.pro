TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++17

LIBS += -lpthread


SOURCES += \
    SantaClaus.cpp \
    santa.cpp \
    deer.cpp \
    elve.cpp

HEADERS += \
    santa.h \
    deer.h \
    elve.h
