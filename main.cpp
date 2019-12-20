#include "n_main.h"

int main() {
    n_Pcap outer_interface("eth1");
    n_Pcap inner_interface("eth0");

    file = new n_Pcap_Data("./test.pcap");

    init();

    while (true){
        // get next packet from interfaces
        n_Frame *input, *output;
        int input_res = outer_interface >> input;
        int output_res = inner_interface >> output;

        // if input packet captured
        if (input_res != 0) {
            //cout << input;
            if(input->what() == "TCP" || input->what().find("TLS") != string::npos){
                n_TCP* input_tcp = dynamic_cast<n_TCP*>(input);
                if (!input_tcp->isFilteredPort(ports)) {
                    inner_interface << input;
                    //cout << input;
                    *file << input;
                } else {
//                    uint8_t* tmp = input->getFrameData();
//                    for (size_t i = 0; i < input->getLength() - 12; i++){
//                        bool isFind = false;
//                        if (!memcmp(tmp + i, "res/asdf.txt", 12)){
//                            cout << "found: " << endl << input;
//                            isFind = true;

//                            memcpy(tmp+i, ".././sdf.txt", 12);
//                            dynamic_cast<n_TCP*>(input)->setProferChecksum();
//                            cout << input;
//                            break;
//                        }
//                    }
                    inner_interface << input;
                    *file << input;
                }
            } else {
                inner_interface << input;
                //cout << input;
                *file << input;
            }
        }

        // if output packet captured
        if (output_res != 0) {
            if(output->what() == "TCP" || output->what().find("TLS") != string::npos){
                n_TCP* output_tcp = dynamic_cast<n_TCP*>(output);
                if (!output_tcp->isFilteredPort(ports)){
                    outer_interface << output;
                    //cout << output;
                    *file << output;
                } else {
                    outer_interface << output;
                    *file << output;
                    //cout << output;
                }
            } else {
                outer_interface << output;
                //cout << output;
                *file << output;
            }
        }
    }
}
