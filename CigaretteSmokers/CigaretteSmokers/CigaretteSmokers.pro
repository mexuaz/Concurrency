TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++17

LIBS += -lpthread


SOURCES += \
    CigaretteSmokers.cpp \
    ingredients.cpp \
    supply_agent.cpp \
    smoker.cpp

HEADERS += \
    ingredients.h \
    supply_agent.h \
    smoker.h
