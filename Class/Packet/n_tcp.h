#ifndef N_TCP_H
#define N_TCP_H
#include <netinet/tcp.h>
#include "Class/Packet/ip.h"

class n_TCP : public IP
{
public:
    n_TCP();
    n_TCP(u_int8_t* data, size_t len);
    n_TCP(const u_int8_t* data, size_t len);
    tcphdr* getTcpData() const;
    std::string what() const override { return "TCP"; }
    //TODO: Add Methods

private:
    tcphdr* tcp_data;
};

#endif // N_TCP_H
