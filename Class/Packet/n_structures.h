#ifndef N_STRUCTURES_H
#define N_STRUCTURES_H
#include <stdint.h>

#pragma pack(push, 1)
typedef struct pseudoHeader {
    uint32_t src;
    uint32_t dst;
    uint8_t reserved;
    uint8_t protocol;
    uint16_t tcplen;
} n_tcp_pseudohdr;

typedef struct {
    uint8_t record_type;
    uint16_t version;
    uint16_t data_length;
} n_tls_record;

typedef struct {
    uint8_t type;
    uint8_t length[3];
} n_tls_handshake;

typedef struct {
    uint8_t data;
} n_tls_change_cipher_spec;

typedef struct {
    uint8_t severity_level;
    uint8_t description;
} n_tls_alert;

typedef struct n_pcap_file_packet_header {
  uint32_t ts_sec;         // timestamp seconds
  uint32_t ts_usec;        // timestamp microseconds
  uint32_t incl_len;       // number of octets of packet saved in file
  uint32_t orig_len;       // actual length of packet
} n_pcap_fpkthdr;
#pragma pack(pop)

namespace n_tls_handshake_type {
    typedef enum n_tls_handshake_type {
        TYPE_ERROR = -1,
        HELLO_REQUEST = 0,
        CLIENT_HELLO,
        SERVER_HELLO,
        CERTIFICATION = 0xb,
        SERVER_KEY_EXCHANGE,
        CERTIFICATE_REQUEST,
        SERVER_DONE,
        CERTIFICATE_VERIFY,
        CLIENT_KEY_EXCHANGE,
        FINISHED = 0x14
    } hsk_type;
}

namespace n_tls_alert_severity {
    typedef enum n_tls_alert_severity {
        TYPE_ERROR = -1,
        WARNING = 0x1,
        FATAL
    } alert_sev;
}

namespace n_tls_alert_descriptions {
    typedef enum n_tls_alert_descriptions {
        TYPE_ERROR = -1,
        CLOSE_NOTIFY = 0,
        UNEXPECTED_MESSAGE = 0xa,
        BAD_RECORD_MAC = 0x14,
        DECOMPRESSION_FAILURE = 0x1e,
        HANDSHAKE_FAILURE = 0x28,
        NO_CERTIFICATE,
        BAD_CERTIFICATE,
        UNSUPPORTED_CERTIFICATE,
        CERTIFICATE_REVOKED,
        CERTIFICATE_EXPIRED,
        CERTIFICATE_UNKNOWN,
        ILLEGAL_PARAMETER,
        UNKNOWN_CA,
        ACCESS_DENIED,
        DECODE_ERROR,
        DECRYPT_ERROR,
        EXPORT_RESTRICTION = 0x3c,
        PROTOCOL_VERSION = 0x46,
        INSUFFICIENT_SECURITY,
        INTERNAL_ERROR = 0x50,
        USER_CANCELLED = 0x5a,
        NO_RENEGOTIATION = 0x64
    } alert_desc;
}


#endif // N_STRUCTURES_H
