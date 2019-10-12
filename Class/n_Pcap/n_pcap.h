#ifndef N_PCAP_H
#define N_PCAP_H
#include <pcap/pcap.h>
#include <iostream>

class n_Pcap
{
public:
    n_Pcap(const char* dev);
    ~n_Pcap();
    pcap_t* getHandle() const { return this->handle; } // return handle
    char* getErrorBuf() { return this->errBuf; } 		// return errBuf
    int sendPacket(const uint8_t* packet_content, int len) const ;
    int getNextPacket();
    pcap_pkthdr* getPacketHeader();
    const uint8_t* getPacketData();
    size_t getPacketLength();

private:
    pcap_t* handle;
    char errBuf[PCAP_ERRBUF_SIZE];
    pcap_pkthdr* header;
    const uint8_t* packet;
};

#endif // N_PCAP_H
