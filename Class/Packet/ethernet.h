#ifndef ETHERNET_H
#define ETHERNET_H

#include <net/ethernet.h>
#include "frame.h"

class Ethernet : public Frame {
public:
    Ethernet();
    Ethernet(uint8_t* data, size_t len);
    Ethernet(const uint8_t* data, size_t len);
    ether_header* getEthernetHeader();
    uint8_t* getEthDst();
    void setEthDst(uint8_t* dst);
    uint8_t* getEthSrc();
    void setEthSrc(uint8_t* src);
    uint16_t getEthType();
    void setEthType(uint16_t eth_type);
    std::string what() override { return "Ethernet"; }

private:
    ether_header* ethernet_data;
};

#endif // ETHERNET_H
