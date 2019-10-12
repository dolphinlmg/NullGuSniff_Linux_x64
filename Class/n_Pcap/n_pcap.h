#ifndef N_PCAP_H
#define N_PCAP_H
#include <pcap/pcap.h>
#include <iostream>

class n_Pcap
{
public:
    n_Pcap(const char* dev);
    ~n_Pcap();
    pcap_t* getHandle() { return this->handle; }
    char* getErrorBuf() { return this->errBuf; }
    int sendPacket(const uint8_t* packet_content, int len);
    int getNextPacket(struct pcap_pkthdr** pkHeader, const uint8_t** pkData);

private:
    pcap_t* handle;
    char errBuf[PCAP_ERRBUF_SIZE];
};

#endif // N_PCAP_H
