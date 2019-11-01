#ifndef N_PCAP_DATA_H
#define N_PCAP_DATA_H
#include <pcap/pcap.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "Class/Packet/n_tls.h"

class n_Pcap_Data
{
public:
    n_Pcap_Data(const char* fileName);
    ~n_Pcap_Data();
    bool push_packet(n_Frame* packet);
    void exportToFile();
    bool operator<<(n_Frame* &packet);

private:
    const char* fileName;
    pcap_file_header* fileHeader;
    std::vector<n_pcap_fpkthdr*> packetHeader;
    std::vector<n_Frame*> packetList;
    std::ofstream os;
};

#endif // N_PCAP_DATA_H
