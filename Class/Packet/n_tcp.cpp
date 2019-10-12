#include "n_tcp.h"

// constructor with uint8_t*
n_TCP::n_TCP(uint8_t* data, size_t len) : n_IP(data, len) {
    this->tcp_data = reinterpret_cast<tcphdr*>(reinterpret_cast<uint8_t*>(this->getIPData()) + this->getSizeOfIPHeader());
}

// constructor with const uint8_t*
n_TCP::n_TCP(const uint8_t* data, size_t len) : n_IP(data, len) {
    this->tcp_data = reinterpret_cast<tcphdr*>(this->getIPData() + this->getSizeOfIPHeader());
}

tcphdr* n_TCP::getTcpData() const {
    return this->tcp_data;
}
