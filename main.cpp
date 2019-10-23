#include "n_main.h"

int main() {
    n_Pcap wlan0("wlan0");
    n_Pcap dummy("dum0");

    file = new n_Pcap_Data("./test.pcap");

    // read ports from 'ports.ng'
    readPortsFromFile();

    while (true){
        // get next packet from wlan0
        int res = wlan0.getNextPacket();
        if (res == 0) continue;
        if (res == -1 || res == -2) break;

        // get appropriate object
        n_Frame* packet = wlan0.recognizePacket();
        // dump packet data
        cout << packet->what() << endl << ": " << packet->getLength() << endl
             << n_Packet::dumpPacket(packet->getFrameData(), packet->getLength()) << endl;

        // continue if packet has filtered ports
        if (packet->what() == "TCP") {
            n_TCP* tmp = dynamic_cast<n_TCP*>(packet);
            if (tmp->isFilteredPort(ports)) continue;
        }
        // only not filtered packet

        // send to another interface
        dummy.sendPacket(packet->getFrameData(), packet->getLength());

        // push&save packet
        file->push_packet(packet);

    }
    return 0;
}
