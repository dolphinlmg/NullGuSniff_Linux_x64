#ifndef N_TLS_H
#define N_TLS_H
#include "Class/Packet/n_tcp.h"

using n_tls_record_type::record_type;
using n_tls_handshake_type::hsk_type;
using n_tls_alert_severity::alert_sev;
using n_tls_alert_descriptions::alert_desc;

class n_TLS : public n_TCP {
public:
    n_TLS(uint8_t* data, pcap_pkthdr* header);
    n_TLS(const uint8_t* data, pcap_pkthdr* header);
    uint8_t getTlsRecordType(size_t i);
    uint16_t getTlsVersion(size_t i);
    uint16_t getTlsDataLength(size_t i);
    std::vector<n_tls_record*> getTlsRecord();
    std::vector<n_tls_handshake*> getTlsHandShake();
    hsk_type getTlsHandshakeType(size_t i) const;
    std::vector<n_tls_change_cipher_spec*> getTlsChangeCipher();
    std::vector<n_tls_alert*> getTlsAlert();
    alert_sev getTlsAlertSeverity(size_t i) const;
    alert_desc getTlsAlertDescription(size_t i) const;
    std::vector<uint8_t*> getTlsApplicationData();
    std::string what() const override;
    friend std::ostream& operator<<(std::ostream& os, n_TLS* &packet);

private:
    std::vector<n_tls_record*> tls_record;
    std::vector<n_tls_handshake*> tls_handshake;
    std::vector<n_tls_change_cipher_spec*> tls_cipher;
    std::vector<n_tls_alert*> tls_alert;
    std::vector<uint8_t*> tls_application_data;
};

#endif // N_TLS_H
