#include <iostream>
#include "Class/Packet/n_tcp.h"
#include "Class/Packet/n_packet.h"
#include "Class/n_Pcap/n_pcap.h"

using namespace std;

int main() {
    n_Pcap pcap_1("wlp0s20f3");
    n_Pcap dummy("dum0");

    while (true){
        int res = pcap_1.getNextPacket();
        if (res == 0) continue;
        if (res == -1 || res == -2) break;
        n_Frame* packet = n_Packet::recognizePacket(pcap_1.getPacketData(), pcap_1.getPacketLength());

        cout << packet->what() << endl
             << n_Packet::dumpPacket(packet->getFrameData(), packet->getLength()) << endl;
        dummy.sendPacket(packet->getFrameData(), packet->getLength());
    }
    return 0;
}
