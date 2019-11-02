#ifndef N_MAIN_H
#define N_MAIN_H
#include <iostream>
#include <fstream>
#include <signal.h>
#include <map>
#include "Class/Packet/n_tls.h"
#include "Class/n_Pcap/n_pcap.h"
#include "Class/n_Pcap/n_pcap_data.h"

using namespace std;
using n_tls_handshake_type::hsk_type;
using n_tls_alert_severity::alert_sev;
using n_tls_alert_descriptions::alert_desc;

// namespace for main
namespace MAIN {
    [[ noreturn ]] void handler(int);
    bool readPortsFromFile();
    bool createMacAddresses();
    uint32_t parseIP(const char* ip);
    uint8_t* parseMAC(const char* mac);

    static n_Pcap_Data* file;
    static vector<uint16_t> ports;
    static vector<pair<pair<uint32_t, uint32_t>, pair<uint16_t, uint16_t>>> sessions;
    static const char* portFileName = "ports.ng";

    // signal handler for sigint
    [[ noreturn ]] void handler(int s) {
        cout << endl << "Signal Captured: " << s
             << endl << "Exporting to file..." << endl;
        file->exportToFile();
        exit(0);
    }

    // read filtering port from file 'ports.ng'
    bool readPortsFromFile() {
        try {
            ifstream is(portFileName, ios::in);
            if (!is.is_open())
                return false;
            uint16_t tmp;
            while(!is.eof()){
                is >> tmp;
                if (is.good())
                    ports.push_back(tmp);
            }
            is.close();
        } catch (exception& ex) {
           cerr << ex.what() << endl;
           return false;
        }
       return true;
    }

    void init() {
        // read ports from 'ports.ng'
        if (!readPortsFromFile()) {
            cerr << "Error to read port file!" << endl;
            exit(-1);
        }

        // register signal handler
        signal(SIGINT, handler);
    }

    // return uint32_t from string ip
    uint32_t parseIP(const char* ip) {
        uint32_t ret = 0;
        uint8_t* p = reinterpret_cast<uint8_t*>(&ret);
        for (size_t i = 0; i < strlen(ip); i++) {
            if (*(ip + i) == '.')
                p++;
            else {
                *p *= 10;
                *p += *(ip + i) - '0';
            }
        }
        return ret;
    }

    // return uint8_t* from string mac
    // string mac should be base on lower case
    uint8_t* parseMAC(const char* mac) {
        uint8_t* ret = new uint8_t[6] {0, };
        for (size_t i = 0; i < strlen(mac); i++) {
            if (*(mac + i) == ':')
                ret++;
            else {
                *ret *= 16;
                *ret += (*(mac + i) >= 'a') ? (*(mac + i) - 'a' + 10) : (*(mac + i) - '0');
            }
        }

        return ret - 5;
    }

}

using namespace MAIN;

#endif // N_MAIN_H
