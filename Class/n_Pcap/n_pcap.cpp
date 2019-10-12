#include "n_pcap.h"

n_Pcap::n_Pcap(const char* dev) {
    this->handle = pcap_open_live(dev, BUFSIZ, 1, 1, this->errBuf);
    if (handle == nullptr)
        std::cerr << "Cannot open device: " << dev << std::endl;
    this->header = nullptr;
    this->packet = nullptr;
}

n_Pcap::~n_Pcap() {
    pcap_close(this->handle);
}

int n_Pcap::sendPacket(const uint8_t* packet_content, int len) const {
    return pcap_sendpacket(this->handle, packet_content, len);
}

int n_Pcap::getNextPacket() {
    return pcap_next_ex(this->handle, &this->header, &this->packet);
}

pcap_pkthdr* n_Pcap::getPacketHeader() {
    return this->header;
}

const uint8_t* n_Pcap::getPacketData() {
    return this->packet;
}

size_t n_Pcap::getPacketLength(){
    if (this->header != nullptr)
        return this->header->len;
    return 0;
}
