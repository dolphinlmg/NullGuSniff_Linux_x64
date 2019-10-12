#include "n_pcap.h"

n_Pcap::n_Pcap(const char* dev) {
    this->handle = pcap_open_live(dev, BUFSIZ, 1, 1, this->errBuf);
    if (handle == nullptr)
        std::cerr << "Cannot open device: " << dev << std::endl;
}

n_Pcap::~n_Pcap() {
    pcap_close(this->handle);
}

int n_Pcap::sendPacket(const uint8_t* packet_content, int len) {
    return pcap_sendpacket(this->handle, packet_content, len);
}

int n_Pcap::getNextPacket(struct pcap_pkthdr** pkHeader, const uint8_t** pkData) {
    return pcap_next_ex(this->handle, pkHeader, pkData);
}
