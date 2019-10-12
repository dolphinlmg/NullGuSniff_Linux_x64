#ifndef N_TCP_H
#define N_TCP_H
#include <netinet/tcp.h>
#include "n_ip.h"

class n_TCP : public n_IP
{
public:
    n_TCP(uint8_t* data, size_t len);
    n_TCP(const uint8_t* data, size_t len);
    tcphdr* getTcpData() const;
    std::string what() const override { return "TCP"; }
    //TODO: Add Methods

private:
    tcphdr* tcp_data;
};

#endif // N_TCP_H
