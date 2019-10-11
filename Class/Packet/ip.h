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
    iphdr* getIPData();
    uint32_t getDst();
    void setDst();
    uint32_t getSrc();
    void setSrc();
    uint8_t getProtocol();

private:
    iphdr* ip_data;
};

#endif // IP_H
