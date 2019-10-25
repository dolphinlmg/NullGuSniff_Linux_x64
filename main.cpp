#include "n_main.h"

int main() {
    n_Pcap wlan0("wlan0");
    n_Pcap dum0("dum0");

    file = new n_Pcap_Data("./test.pcap");

    init();

    while (true){
        // get next packet from interfaces
        n_Frame *input, *output;
        int input_res = wlan0 >> input;
        int output_res = dum0 >> output;

        // if input packet captured
        if (input_res != 0) {
            dynamic_cast<n_Ethernet*>(input)->setEthSrc(parseMAC("00:e0:4c:61:54:a8"));
            dynamic_cast<n_Ethernet*>(input)->setEthDst(parseMAC("00:e0:4c:61:55:40"));

            // not filtered tcp, or just ip packet change ip address
            if ((input->what() == "TCP" && !dynamic_cast<n_TCP*>(input)->isFilteredPort(ports)) || input->what() == "IP" ) {
                n_IP* input_ip = dynamic_cast<n_IP*>(input);
                input_ip->setIPDst(parseIP("123.24.38.100"));
                input_ip->setProferIPChecksum();
                if (input->what() == "TCP") dynamic_cast<n_TCP*>(input)->setProferTCPChecksum();
            }

            cout <<input;
            dum0 << input;
            *file << input;
        }

        // if output packet captured
        if (output_res != 0) {
            dynamic_cast<n_Ethernet*>(output)->setEthSrc(parseMAC("98:2c:bc:6d:42:5f"));
            dynamic_cast<n_Ethernet*>(output)->setEthDst(parseMAC("88:36:6c:a7:7a:be"));

            // not filtered tcp, or just ip packet change ip address
            if ((input->what() == "TCP" && !dynamic_cast<n_TCP*>(input)->isFilteredPort(ports)) || input->what() == "IP" ) {
                n_IP* output_ip = dynamic_cast<n_IP*>(output);
                output_ip->setIPSrc(parseIP("172.203.0.9"));
                output_ip->setProferIPChecksum();
                if (output->what() == "TCP") dynamic_cast<n_TCP*>(output)->setProferTCPChecksum();
            }

            cout << output;
            wlan0 << output;
            *file << output;
        }
    }
}
