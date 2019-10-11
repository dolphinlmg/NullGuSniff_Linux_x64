#include "ip.h"

IP::IP(){}
IP::IP(uint8_t* data, size_t len) : Ethernet (data, len){}
IP::IP(const uint8_t* data, size_t len) : Ethernet (data, len){}

iphdr* IP::getIPData(){}
uint32_t IP::getDst(){}
void IP::setDst(){}
uint32_t IP::getSrc(){}
void IP::setSrc(){}
uint8_t IP::getProtocol(){}
