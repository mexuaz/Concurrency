TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++17

LIBS += -lpthread


SOURCES += \
    FIFOBarbershop.cpp \
    barber.cpp \
    customer.cpp

HEADERS += \
    barber.h \
    customer.h
