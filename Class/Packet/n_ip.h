#ifndef n_IP_H
#define n_IP_H
#include <netinet/ip.h>
#include "n_ethernet.h"

class n_IP : public n_Ethernet
{
public:
    n_IP(uint8_t* data, pcap_pkthdr* header);
    n_IP(const uint8_t* data, pcap_pkthdr* header);
    iphdr* getIPHeader() const ;
    uint32_t getIPDst() const ;
    void setIPDst(uint32_t addr);
    uint32_t getIPSrc() const ;
    void setIPSrc(uint32_t addr);
    void setIPSize(uint16_t length);
    uint8_t getProtocol() const ;
    uint32_t getSizeOfIPHeader() const ;
    std::string what() const override { return "IP"; }
    uint16_t calcIPChecksum();
    void setIPChecksum(uint16_t checksum);
    void setProferIPChecksum();

private:
    iphdr* ip_header;
};

#endif // n_IP_H
