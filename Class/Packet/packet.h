#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <cstring>

class Packet {
public:
    Packet();
    Packet(uint8_t* data, size_t len);
    Packet(const uint8_t* data, size_t len);
    ~Packet();
    void setLength(unsigned int len);
    unsigned int getLength();
    void setPacketData(uint8_t* data, size_t len);
    uint8_t* getPacketData();

private:
    unsigned int length;
    uint8_t* data;
};

#endif // PACKET_H
