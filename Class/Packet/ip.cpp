#include "ip.h"

IP::IP(){}
IP::IP(uint8_t* data, size_t len) : Ethernet (data, len){
    this->ip_data = reinterpret_cast<iphdr*>(this->getPacketData() + sizeof(ether_header));
}
IP::IP(const uint8_t* data, size_t len) : Ethernet (data, len){
    this->ip_data = reinterpret_cast<iphdr*>(this->getPacketData() + sizeof(ether_header));
}

iphdr* IP::getIPData(){
    return this->ip_data;
}

uint32_t IP::getDst(){
    return this->ip_data->daddr;
}

void IP::setDst(uint32_t addr){
    this->ip_data->daddr = addr;
}

uint32_t IP::getSrc(){
    return this->ip_data->daddr;
}

void IP::setSrc(uint32_t addr){
    this->ip_data->saddr = addr;
}

uint8_t IP::getProtocol(){
    return this->ip_data->protocol;
}
