#include "packet.h"

Frame* Packet::recognizePacket(uint8_t* data, size_t len) {
    Frame* ret = new Ethernet(data, len);
    if (dynamic_cast<Ethernet*>(ret)->getEthType() == ntohs(0x0800)){
        delete ret;
        ret = new IP(data, len);
        if (dynamic_cast<IP*>(ret)->getProtocol() == 6){
            delete ret;
            ret = new n_TCP(data, len);
        }
    }
    return ret;
}
