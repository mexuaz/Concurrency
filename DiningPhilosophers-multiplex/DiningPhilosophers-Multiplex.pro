TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++17

LIBS += -lpthread


SOURCES += \
    philosopher.cpp \
    fork.cpp \
    spaghetti_bowl.cpp \
    DiningPhilosophers-Multiplex.cpp

HEADERS += \
    philosopher.h \
    fork.h \
    spaghetti_bowl.h
