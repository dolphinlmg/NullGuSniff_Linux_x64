#include <iostream>
#include "Class/Packet/n_tcp.h"
#include "Class/Packet/n_packet.h"
#include "Class/n_Pcap/n_pcap.h"

using namespace std;

int main() {
    n_Pcap pcap_1("wlp0s20f3");

    while (true){
        int res = pcap_1.getNextPacket();
        if (res == 0) continue;
        if (res == -1 || res == -2) break;
        cout << n_Packet::dumpPacket(pcap_1.getPacketData(), pcap_1.getPacketLength()) << endl;
    }
    return 0;
}
