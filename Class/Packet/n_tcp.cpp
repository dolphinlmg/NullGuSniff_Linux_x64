#include "n_tcp.h"
#include <iostream>

// constructor with uint8_t*
n_TCP::n_TCP(uint8_t* data, pcap_pkthdr* header) : n_IP(data, header) {
    this->tcp_header = reinterpret_cast<tcphdr*>(reinterpret_cast<uint8_t*>(this->getIPHeader()) + this->getSizeOfIPHeader());
}

// constructor with const uint8_t*
n_TCP::n_TCP(const uint8_t* data, pcap_pkthdr* header) : n_IP(data, header) {
    this->tcp_header = reinterpret_cast<tcphdr*>(reinterpret_cast<uint8_t*>(this->getIPHeader()) + this->getSizeOfIPHeader());
}

// return tcphdr*
tcphdr* n_TCP::getTcpHeader() const {
    return this->tcp_header;
}

// return size of tcp header
uint32_t n_TCP::getSizeOfTcpHeader() const {
    return unsigned(this->tcp_header->th_off << 2);
}

// return is this packet is tls
bool n_TCP::isTLS() const {
    if (this->getLength() == sizeof(ethhdr) + this->getSizeOfIPHeader() + this->getSizeOfTcpHeader())
        return false;
    uint8_t* tmp = reinterpret_cast<uint8_t*>(this->getTcpHeader()) + this->getSizeOfTcpHeader();
    return (*tmp >= 0x14) && (*tmp <= 0x17);
}

bool n_TCP::isFilteredDstPort(std::vector<uint16_t> v) const {
    for (auto a : v) {
        if (ntohs(this->tcp_header->th_dport) == a)
            return true;
    }
    return false;
}

bool n_TCP::isFilteredDstPort(uint16_t port) const {
    return (ntohs(this->tcp_header->th_dport) == port);
}

bool n_TCP::isFilteredSrcPort(std::vector<uint16_t> v) const {
    for (auto a : v) {
        if (ntohs(this->tcp_header->th_sport) == a)
            return true;
    }
    return false;
}

bool n_TCP::isFilteredSrcPort(uint16_t port) const {
    return (ntohs(this->tcp_header->th_sport) == port);
}

// return true if the packet is filtered port
bool n_TCP::isFilteredPort(std::vector<uint16_t> v) const {
    return this->isFilteredDstPort(v) | this->isFilteredSrcPort(v);
}

// calculate checksum
uint16_t n_TCP::in_checksum(uint16_t *ptr,int nbytes) {
        long sum;
        unsigned short oddbyte;
        unsigned short answer;

        sum=0;
        while(nbytes>1) {
                sum+=*ptr++;
                nbytes-=2;
        }
        if(nbytes==1) {
                oddbyte=0;
                *(reinterpret_cast<uint8_t*>(&oddbyte))=*reinterpret_cast<uint8_t*>(ptr);
                sum+=oddbyte;
        }

        sum = (sum>>16)+(sum & 0xffff);
        sum = sum + (sum>>16);
        answer=static_cast<uint16_t>(~sum);

        return answer;
}

// setting up & calculate tcp checksum
uint16_t n_TCP::calcTCPChecksum() {
    uint16_t dataLen = static_cast<uint16_t>(this->getLength() - sizeof(ethhdr) - this->getSizeOfIPHeader());
    n_tcp_pseudohdr hdr = {this->getIPSrc(), this->getIPDst(), 0, this->getIPHeader()->protocol,
                     htons(dataLen)};
    tcphdr* tcp = reinterpret_cast<tcphdr*>(new uint8_t[dataLen]);
    uint8_t* tmphdr = new uint8_t[sizeof(n_tcp_pseudohdr) + dataLen];
    memcpy(tcp, this->getTcpHeader(), dataLen);
    tcp->check = 0;

    memcpy(tmphdr, &hdr, sizeof(n_tcp_pseudohdr));
    memcpy(tmphdr + sizeof(n_tcp_pseudohdr), tcp, dataLen);

    uint16_t ret = in_checksum(reinterpret_cast<uint16_t*>(tmphdr), sizeof(n_tcp_pseudohdr) + dataLen);

    if (this->getFrameHeader()->len == 60)
        ret = ntohs(htons(ret) + 6);
    delete[] tcp;
    delete[] tmphdr;

    return ret;
}

// set checksum
void n_TCP::setTCPChecksum(uint16_t checksum) {
    this->tcp_header->check = checksum;
}

// set profer checksum for tcp
void n_TCP::setProferTCPChecksum() {
    this->setTCPChecksum(this->calcTCPChecksum());
}

// set profer checksum for ip, tcp
void n_TCP::setProferChecksum() {
    this->setProferIPChecksum();
    this->setProferTCPChecksum();
}

void n_TCP::setTcpDstPort(uint16_t port) {
    this->tcp_header->dest = htons(port);
}

uint16_t n_TCP::getTcpDstPort() const {
    return ntohs(this->tcp_header->dest);
}

void n_TCP::setTcpSrcPort(uint16_t port) {
    this->tcp_header->source = htons(port);
}

uint16_t n_TCP::getTcpSrcPort() const {
    return ntohs(this->tcp_header->source);
}
