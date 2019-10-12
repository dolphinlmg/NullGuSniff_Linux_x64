#include "n_tcp.h"

n_TCP::n_TCP() {}

n_TCP::n_TCP(u_int8_t* data, size_t len) : n_IP(data, len) {
    this->tcp_data = reinterpret_cast<tcphdr*>(reinterpret_cast<uint8_t*>(this->getIPData()) + this->getSizeOfIPHeader());
}

n_TCP::n_TCP(const u_int8_t* data, size_t len) : n_IP(data, len) {
    this->tcp_data = reinterpret_cast<tcphdr*>(this->getIPData() + this->getSizeOfIPHeader());
}

tcphdr* n_TCP::getTcpData() const {
    return this->tcp_data;
}
