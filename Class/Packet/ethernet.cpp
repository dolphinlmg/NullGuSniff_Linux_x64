#include "ethernet.h"

Ethernet::Ethernet() {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getPacketData());
}

Ethernet::Ethernet(uint8_t* data, size_t len) : Packet(data, len) {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getPacketData());
}

Ethernet::Ethernet(const uint8_t* data, size_t len) : Packet(data, len) {
    this->ethernet_data = reinterpret_cast<ether_header*>(this->getPacketData());
}

ether_header* Ethernet::getEthernetHeader(){
    return this->ethernet_data;
}

uint8_t* Ethernet::getEthDst(){
    return this->ethernet_data->ether_dhost;
}

void Ethernet::setEthDst(uint8_t* dst){
    memcpy(this->ethernet_data->ether_dhost, dst, 6);
}

uint8_t* Ethernet::getEthSrc(){
    return this->ethernet_data->ether_shost;
}

void Ethernet::setEthSrc(uint8_t* src){
    memcpy(this->ethernet_data->ether_shost, src, 6);
}

uint16_t Ethernet::getEthType(){
    return this->ethernet_data->ether_type;
}

void Ethernet::setEthType(uint16_t eth_type){
    this->ethernet_data->ether_type = eth_type;
}
