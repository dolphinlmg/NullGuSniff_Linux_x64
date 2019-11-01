#include "n_tls.h"

n_TLS::n_TLS(uint8_t* data, pcap_pkthdr* header) : n_TCP(data, header) {
    this->tls_record = reinterpret_cast<n_tls_record*>(
                reinterpret_cast<uint8_t*>(this->getTcpHeader()) + this->getSizeOfTcpHeader());

    if (this->tls_record->record_type == 0x16) {
        this->tls_handshake = reinterpret_cast<n_tls_handshake*>(
                    reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record));
    } else if (this->tls_record->record_type == 0x14) {
        this->tls_cipher = reinterpret_cast<n_tls_change_cipher_spec*>(
                    reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record));
    } else if (this->tls_record->record_type == 0x15) {
        this->tls_alert = reinterpret_cast<n_tls_alert*>(
                    reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record));
    } else if (this->tls_record->record_type == 0x17) {
        this->tls_application_data = reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record);
    }
}

n_TLS::n_TLS(const uint8_t* data, pcap_pkthdr* header) : n_TCP(data, header) {
    this->tls_record = reinterpret_cast<n_tls_record*>(
                reinterpret_cast<uint8_t*>(this->getTcpHeader()) + this->getSizeOfTcpHeader());

    if (this->tls_record->record_type == 0x16) {
        this->tls_handshake = reinterpret_cast<n_tls_handshake*>(
                    reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record));
    } else if (this->tls_record->record_type == 0x14) {
        this->tls_cipher = reinterpret_cast<n_tls_change_cipher_spec*>(
                    reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record));
    } else if (this->tls_record->record_type == 0x15) {
        this->tls_alert = reinterpret_cast<n_tls_alert*>(
                    reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record));
    } else if (this->tls_record->record_type == 0x17) {
        this->tls_application_data = reinterpret_cast<uint8_t*>(this->tls_record) + sizeof(n_tls_record);
    }
}

uint8_t n_TLS::getTlsRecordType() {
    return this->tls_record->record_type;
}

uint16_t n_TLS::getTlsVersion() {
    return ntohs(this->tls_record->version);
}

uint16_t n_TLS::getTlsDataLength() {
    return ntohs(this->tls_record->data_length);
}

std::string n_TLS::what() const {
    if (this->tls_alert != nullptr) return "TLS_Alert";
    else if (this->tls_cipher != nullptr) return "TLS_Cipher";
    else if (this->tls_handshake != nullptr) return "TLS_Handshake";
    return "TLS_Recognization_Error!";
}
