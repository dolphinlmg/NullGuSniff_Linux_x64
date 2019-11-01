#ifndef N_TLS_H
#define N_TLS_H
#include "Class/Packet/n_tcp.h"

class n_TLS : public n_TCP {
public:
    n_TLS(uint8_t* data, pcap_pkthdr* header);
    n_TLS(const uint8_t* data, pcap_pkthdr* header);
    uint8_t getTlsRecordType();
    uint16_t getTlsVersion();
    uint16_t getTlsDataLength();
    n_tls_record* getTlsRecord();
    n_tls_handshake* getTlsHandShake();
    n_tls_change_cipher_spec* getTlsChangeCipher();
    n_tls_alert* getTlsAlert();
    uint8_t* getTlsApplicationData();
    std::string what() const override;

private:
    n_tls_record* tls_record;
    n_tls_handshake* tls_handshake { nullptr };
    n_tls_change_cipher_spec* tls_cipher { nullptr };
    n_tls_alert* tls_alert { nullptr };
    uint8_t* tls_application_data;
};

#endif // N_TLS_H
