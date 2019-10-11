TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Class/Packet/ethernet.cpp \
    Class/Packet/ip.cpp \
        Class/Packet/packet.cpp \
        main.cpp \

HEADERS += \
    Class/Packet/ethernet.h \
    Class/Packet/ip.h \
    Class/Packet/packet.h
