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
            cout << input;
            inner_interface << input;
            *file << input;
        }

        // if output packet captured
        if (output_res != 0) {
            cout << output;
            outer_interface << output;
            *file << output;
        }
    }
}
