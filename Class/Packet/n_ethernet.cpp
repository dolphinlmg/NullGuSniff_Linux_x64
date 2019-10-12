#include "n_ethernet.h"

n_Ethernet::n_Ethernet(){}

n_Ethernet::n_Ethernet(uint8_t* data, size_t len) : n_Frame(data, len) {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getFrameData());
}

n_Ethernet::n_Ethernet(const uint8_t* data, size_t len) : n_Frame(data, len) {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getFrameData());
}

ether_header* n_Ethernet::getEthernetHeader() const {
    return this->ethernet_data;
}

uint8_t* n_Ethernet::getEthDst() const {
    return this->ethernet_data->ether_dhost;
}

void n_Ethernet::setEthDst(uint8_t* dst){
    memcpy(this->ethernet_data->ether_dhost, dst, 6);
}

uint8_t* n_Ethernet::getEthSrc() const {
    return this->ethernet_data->ether_shost;
}

void n_Ethernet::setEthSrc(uint8_t* src){
    memcpy(this->ethernet_data->ether_shost, src, 6);
}

uint16_t n_Ethernet::getEthType() const {
    return this->ethernet_data->ether_type;
}

void n_Ethernet::setEthType(uint16_t eth_type){
    this->ethernet_data->ether_type = eth_type;
}

