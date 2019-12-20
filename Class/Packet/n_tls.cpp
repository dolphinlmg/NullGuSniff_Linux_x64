#include "n_tls.h"

n_TLS::n_TLS(uint8_t* data, pcap_pkthdr* header) : n_TCP(data, header) {
    size_t size = sizeof(ethhdr) + this->getSizeOfIPHeader() + this->getSizeOfTcpHeader();
    while (size < header->len) {
        n_tls_record* tmp = reinterpret_cast<n_tls_record*>(data + size);
        this->tls_record.push_back(tmp);
        switch (tmp->record_type) {
        case record_type::ALERT:
            this->tls_alert.push_back(reinterpret_cast<n_tls_alert*>(data + size + sizeof(n_tls_record)));
            break;
        case record_type::HANDSHAKE:
            this->tls_handshake.push_back(reinterpret_cast<n_tls_handshake*>(data + size + sizeof(n_tls_record)));
            break;
        case record_type::APPLICATION_DATA:
            this->tls_application_data.push_back(reinterpret_cast<uint8_t*>(data + size + sizeof(n_tls_record)));
            break;
        case record_type::CHANGE_CHIPER_SPEC:
            this->tls_cipher.push_back(reinterpret_cast<n_tls_change_cipher_spec*>(data + size + sizeof(n_tls_record)));
            break;
        default:
            break;
        }
        size += sizeof(n_tls_record) + tmp->data_length;
    }
}

n_TLS::n_TLS(const uint8_t* data, pcap_pkthdr* header) : n_TCP(data, header) {
   size_t size = sizeof(ethhdr) + this->getSizeOfIPHeader() + this->getSizeOfTcpHeader();
    while (size < header->len) {
        n_tls_record* tmp = reinterpret_cast<n_tls_record*>(this->getFrameData() + size);
        this->tls_record.push_back(tmp);
        switch (tmp->record_type) {
        case record_type::ALERT:
            this->tls_alert.push_back(reinterpret_cast<n_tls_alert*>(this->getFrameData() + size + sizeof(n_tls_record)));
            break;
        case record_type::HANDSHAKE:
            this->tls_handshake.push_back(reinterpret_cast<n_tls_handshake*>(this->getFrameData() + size + sizeof(n_tls_record)));
            break;
        case record_type::APPLICATION_DATA:
            this->tls_application_data.push_back(reinterpret_cast<uint8_t*>(this->getFrameData() + size + sizeof(n_tls_record)));
            break;
        case record_type::CHANGE_CHIPER_SPEC:
            this->tls_cipher.push_back(reinterpret_cast<n_tls_change_cipher_spec*>(this->getFrameData() + size + sizeof(n_tls_record)));
            break;
        default:
            break;
        }
        size += sizeof(n_tls_record) + ntohs(tmp->data_length);
    }
}

// get tls record type in index i
uint8_t n_TLS::getTlsRecordType(size_t i) {
    if (this->tls_record.size() > i)
        return this->tls_record.at(i)->record_type;
    return 0;
}

// get tls record version in index i
uint16_t n_TLS::getTlsVersion(size_t i) {
    if (this->tls_record.size() > i)
        return ntohs(this->tls_record.at(i)->version);
    return 0;
}

// get tls record data length by index i
uint16_t n_TLS::getTlsDataLength(size_t i) {
    if (this->tls_record.size() > i)
        return ntohs(this->tls_record.at(i)->data_length);
    return 0;
}

// get tls records vector
std::vector<n_tls_record*> n_TLS::getTlsRecord() {
    return this->tls_record;
}

// get tls handshakes vector
std::vector<n_tls_handshake*> n_TLS::getTlsHandShake() {
    return this->tls_handshake;
}

// get handshake type by index i
hsk_type n_TLS::getTlsHandshakeType(size_t i) const {
    if (this->tls_handshake.size() > i)
        return static_cast<hsk_type>(this->tls_handshake.at(i)->type);
    return hsk_type::TYPE_ERROR;
}

// get tls ciphers vector
std::vector<n_tls_change_cipher_spec*> n_TLS::getTlsChangeCipher() {
    return this->tls_cipher;
}

// get tls alerts vecter
std::vector<n_tls_alert*> n_TLS::getTlsAlert() {
    return this->tls_alert;
}

// get tls alert severity by index i
alert_sev n_TLS::getTlsAlertSeverity(size_t i) const {
    if (this->tls_alert.size() > i)
       return static_cast<alert_sev>(this->tls_alert.at(i)->severity_level);
    return alert_sev::TYPE_ERROR;
}

// get tls alert description by index i
alert_desc n_TLS::getTlsAlertDescription(size_t i) const {
    if (this->tls_alert.size() > i)
        return static_cast<alert_desc>(this->tls_alert.at(i)->description);
    return alert_desc::TYPE_ERROR;
}

// get tls application data vector
std::vector<uint8_t*> n_TLS::getTlsApplicationData() {
    return this->tls_application_data;
}

std::string n_TLS::what() const {
    std::string ret;
    if (this->tls_alert.size() > 0) ret += "TLS_Alert ";
    if (this->tls_cipher.size() > 0) ret += "TLS_Cipher ";
    if (this->tls_handshake.size() > 0) ret += "TLS_Handshake ";
    if (this->tls_application_data.size() > 0) ret += "TLS_Application_Data ";

    if (ret == "")
        return "TLS_Recognization_Error!";
    return ret;
}

std::ostream& operator<<(std::ostream& os, n_TLS* &packet) {
    os << packet->what() << "\n RECORD TYPE: ";
    for (size_t i = 0; i < packet->getTlsRecord().size(); i++)
        os << signed(packet->getTlsRecordType(i)) << ", ";
    os << "\b\b \n size: " << packet->getLength() << " hex: 0x" << std::hex << packet->getLength() << std::dec<< std::endl
       << packet->dumpPacket() << std::endl;
    return os;
}
