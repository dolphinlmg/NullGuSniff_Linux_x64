#include "n_packet.h"
#include <iostream>
#include <stdio.h>

n_Frame* n_Packet::recognizePacket(uint8_t* data, size_t len) {
    n_Frame* ret = new n_Ethernet(data, len);
    if (dynamic_cast<n_Ethernet*>(ret)->getEthType() == ntohs(0x0800)){
        delete ret;
        ret = new n_IP(data, len);
        if (dynamic_cast<n_IP*>(ret)->getProtocol() == 6){
            delete ret;
            ret = new n_TCP(data, len);
        }
    }
    return ret;
}

template<class Elem, class Traits>
inline void hex_dump(const void* aData, std::size_t aLength, std::basic_ostream<Elem, Traits>& aStream, std::size_t aWidth = 16)
{
    const char* const start = static_cast<const char*>(aData);
    const char* const end = start + aLength;
    const char* line = start;
    while (line != end)
    {
        aStream.width(4);
        aStream.fill('0');
        aStream << std::hex << line - start << " : ";
        std::size_t lineLength = std::min(aWidth, static_cast<std::size_t>(end - line));
        for (std::size_t pass = 1; pass <= 2; ++pass)
        {
            for (const char* next = line; next != end && next != line + aWidth; ++next)
            {
                char ch = *next;
                switch(pass)
                {
                case 2:
                    aStream << (ch < 32 ? '.' : ch);
                    break;
                case 1:
                    if (next != line)
                        aStream << " ";
                    aStream.width(2);
                    aStream.fill('0');
                    aStream << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(ch));
                    break;
                }
            }
            if (pass == 1 && lineLength != aWidth)
                aStream << std::string(aWidth * 3 - lineLength * 3, ' ');
            aStream << " ";
        }
        aStream << std::endl;
        line = line + lineLength;
    }
}

std::string n_Packet::dumpPacket(const uint8_t* data, size_t len) {
    std::stringstream ss;
    hex_dump(data, len, ss);
    return ss.str();
}
