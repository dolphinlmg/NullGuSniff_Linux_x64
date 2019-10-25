#include "n_main.h"

int main() {
    n_Pcap wlan0("wlan0");
    n_Pcap eth0("eth0");

    file = new n_Pcap_Data("./test.pcap");

    init();

    while (true){
        // get next packet from interfaces
        n_Frame *input, *output;
        int input_res = wlan0 >> input;
        int output_res = eth0 >> output;

        // break if error occured
        if (input_res == -1 || input_res == -2 || output_res == -1 || output_res == -2) break;

        // if input packet captured
        if (input_res != 0) {
            dynamic_cast<n_Ethernet*>(input)->setEthSrc(reinterpret_cast<const uint8_t*>("\x00\xe0\x4c\x61\x54\xa8"));
            dynamic_cast<n_Ethernet*>(input)->setEthDst(reinterpret_cast<const uint8_t*>("\x00\xe0\x4c\x61\x55\x40"));
            if (input->what() == "TCP"){
                n_TCP* input_tcp = dynamic_cast<n_TCP*>(input);

                if (!input_tcp->isFilteredDstPort(ports)) {
                    input_tcp->setIPDst(parseIP("123.24.38.100"));
                    input_tcp->setProferChecksum();
                }
            } else if (input->what() == "IP") {
                n_IP* input_ip = dynamic_cast<n_IP*>(input);
                if (input_ip->getIPData()->protocol == 1)
                    cout << "found" << endl;

                input_ip->setIPDst(parseIP("123.24.38.100"));
                input_ip->setProferIPChecksum();
            }

            cout <<input;
            eth0 << input;
            *file << input;
        }

        // if output packet captured
        if (output_res != 0) {
            dynamic_cast<n_Ethernet*>(output)->setEthSrc(reinterpret_cast<const uint8_t*>("\x98\x2c\xbc\x6d\x42\x5f"));
            dynamic_cast<n_Ethernet*>(output)->setEthDst(reinterpret_cast<const uint8_t*>("\x88\x36\x6c\xa7\x7a\xbe"));
            if (output->what() == "TCP"){
                n_TCP* output_tcp = dynamic_cast<n_TCP*>(output);

                if (!output_tcp->isFilteredPort(ports)) {
                    output_tcp->setIPSrc(parseIP("172.203.0.9"));
                    output_tcp->setProferChecksum();
                }
            } else if (output->what() == "IP") {
                    n_IP* output_ip = dynamic_cast<n_IP*>(output);

                    if (output_ip->getIPData()->protocol == 1)
                        cout << "found" << endl;

                    output_ip->setIPSrc(parseIP("172.203.0.9"));
                    output_ip->setProferIPChecksum();
                }

            cout << output;
            wlan0 << output;
            *file << output;
        }
    }
    return 0;
}
