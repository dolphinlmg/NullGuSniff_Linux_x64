#ifndef IP_H
#define IP_H
#include <netinet/ip.h>
#include "ethernet.h"

class IP : public Ethernet
{
public:
    IP();
    IP(uint8_t* data, size_t len);
    IP(const uint8_t* data, size_t len);
    iphdr* getIPData() const ;
    uint32_t getDst() const ;
    void setDst(uint32_t addr);
    uint32_t getSrc() const ;
    void setSrc(uint32_t addr);
    uint8_t getProtocol() const ;
    size_t getSizeOfIPHeader() const ;
    std::string what() const override { return "IP"; }

private:
    iphdr* ip_data;
};

#endif // IP_H
