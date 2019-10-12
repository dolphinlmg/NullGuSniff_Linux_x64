#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <cstring>
#include <sstream>
#include "n_tcp.h"

class n_Packet {
public:
    n_Packet();
    static n_Frame* recognizePacket(const uint8_t* data, int len);
    static std::string dumpPacket(const uint8_t* data, int len);

};

#endif // PACKET_H
