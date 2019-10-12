#include "ethernet.h"

Ethernet::Ethernet(){}

Ethernet::Ethernet(uint8_t* data, size_t len) : Frame(data, len) {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getFrameData());
}

Ethernet::Ethernet(const uint8_t* data, size_t len) : Frame(data, len) {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getFrameData());
}

ether_header* Ethernet::getEthernetHeader() const {
    return this->ethernet_data;
}

uint8_t* Ethernet::getEthDst() const {
    return this->ethernet_data->ether_dhost;
}

void Ethernet::setEthDst(uint8_t* dst){
    memcpy(this->ethernet_data->ether_dhost, dst, 6);
}

uint8_t* Ethernet::getEthSrc() const {
    return this->ethernet_data->ether_shost;
}

void Ethernet::setEthSrc(uint8_t* src){
    memcpy(this->ethernet_data->ether_shost, src, 6);
}

uint16_t Ethernet::getEthType() const {
    return this->ethernet_data->ether_type;
}

void Ethernet::setEthType(uint16_t eth_type){
    this->ethernet_data->ether_type = eth_type;
}

