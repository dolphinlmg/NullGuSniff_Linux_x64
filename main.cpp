#include "n_main.h"

int main() {
    n_Pcap wlan0("wlan0");
    n_Pcap dummy("dum0");

    file = new n_Pcap_Data("./test.pcap");

    init();

    while (true){
        // get next packet from interfaces
        n_Frame *input, *output;
        int input_res = wlan0 >> input;
        int output_res = dummy >> output;

        // break if error occured
        if (input_res == -1 || input_res == -2 || output_res == -1 || output_res == -2) break;

        // if input packet captured
        if (input_res != 0) {
            dynamic_cast<n_Ethernet*>(input)->setEthDst(reinterpret_cast<const uint8_t*>("\xff\xff\xff\xff\xff\xff"));
            if (input->what() == "TCP"){
                n_TCP* input_tcp = dynamic_cast<n_TCP*>(input);

                if (!input_tcp->isFilteredDstPort(ports)) {
                    input_tcp->setIPSrc(parseIP("172.203.0.22"));
                    input_tcp->setProferChecksum();
                    dummy << input;
                }
            }
            *file << input;
        }

        // if output packet captured
        if (output_res != 0) {
            dynamic_cast<n_Ethernet*>(output)->setEthDst(reinterpret_cast<const uint8_t*>("\xff\xff\xff\xff\xff\xff"));
            if (output->what() == "TCP"){
                n_TCP* output_tcp = dynamic_cast<n_TCP*>(output);

                if (!output_tcp->isFilteredPort(ports)) {
                    output_tcp->setIPDst(parseIP("172.24.1.102"));
                    output_tcp->setProferChecksum();
                    dummy << output;
                }
            }

            *file << output;
        }
    }
    return 0;
}
