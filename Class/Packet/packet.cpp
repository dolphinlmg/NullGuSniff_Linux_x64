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

std::string Packet::dumpPacket(uint8_t* data, size_t len) {
    std::stringstream stream;
    stream.fill('0');
    stream.width(2);
    for (size_t i = 0; i < len; i++){
        if(i != 1 && i % 16 == 0)
            stream << std::endl;
        else if(i != 1 && i % 8 == 0)
            stream << " ";
        stream << *(data + i);
    }
    stream << std::endl;
    return stream.str();
}
