TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap

SOURCES += \
    Class/Packet/ethernet.cpp \
    Class/Packet/frame.cpp \
    Class/Packet/ip.cpp \
    Class/Packet/n_tcp.cpp \
        Class/Packet/packet.cpp \
    Class/n_Pcap/n_pcap.cpp \
        main.cpp

HEADERS += \
    Class/Packet/ethernet.h \
    Class/Packet/frame.h \
    Class/Packet/ip.h \
    Class/Packet/n_tcp.h \
    Class/Packet/packet.h \
    Class/n_Pcap/n_pcap.h
