#include "n_ip.h"

n_IP::n_IP(){}
n_IP::n_IP(uint8_t* data, size_t len) : n_Ethernet (data, len){
    this->ip_data = reinterpret_cast<iphdr*>(this->getFrameData() + sizeof(ether_header));
}
n_IP::n_IP(const uint8_t* data, size_t len) : n_Ethernet (data, len){
    this->ip_data = reinterpret_cast<iphdr*>(this->getFrameData() + sizeof(ether_header));
}

iphdr* n_IP::getIPData() const {
    return this->ip_data;
}

uint32_t n_IP::getDst() const {
    return this->ip_data->daddr;
}

void n_IP::setDst(uint32_t addr){
    this->ip_data->daddr = addr;
}

uint32_t n_IP::getSrc() const {
    return this->ip_data->daddr;
}

void n_IP::setSrc(uint32_t addr){
    this->ip_data->saddr = addr;
}

uint8_t n_IP::getProtocol() const {
    return this->ip_data->protocol;
}
size_t n_IP::getSizeOfIPHeader() const {
    return this->ip_data->ihl * 4;
}
