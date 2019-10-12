#include "n_ip.h"

// constructor with uint8_t*
n_IP::n_IP(uint8_t* data, int len) : n_Ethernet (data, len){
    this->ip_data = reinterpret_cast<iphdr*>(this->getFrameData() + sizeof(ether_header));
}

// constructor with const uint8_t*
n_IP::n_IP(const uint8_t* data, int len) : n_Ethernet (data, len){
    this->ip_data = reinterpret_cast<iphdr*>(this->getFrameData() + sizeof(ether_header));
}

// return iphdr*
iphdr* n_IP::getIPData() const {
    return this->ip_data;
}

// return dest ip addr
uint32_t n_IP::getDst() const {
    return this->ip_data->daddr;
}

// set dest ip addr
void n_IP::setDst(uint32_t addr){
    this->ip_data->daddr = addr;
}

// return source ip addr
uint32_t n_IP::getSrc() const {
    return this->ip_data->daddr;
}

// set source ip addr
void n_IP::setSrc(uint32_t addr){
    this->ip_data->saddr = addr;
}

// return protocol number of ip header
uint8_t n_IP::getProtocol() const {
    return this->ip_data->protocol;
}

// set protocol number of ip header
size_t n_IP::getSizeOfIPHeader() const {
    return this->ip_data->ihl * 4;
}
