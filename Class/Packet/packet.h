#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <cstring>
#include <sstream>
#include "Class/Packet/n_tcp.h"

class Packet {
public:
    Packet();
    static Frame* recognizePacket(uint8_t* data, size_t len);
    static std::string dumpPacket(uint8_t* data, size_t len);

};

#endif // PACKET_H
