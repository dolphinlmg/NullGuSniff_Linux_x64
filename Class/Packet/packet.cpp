#include "packet.h"

Packet::Packet() { this->data = nullptr; }

Packet::Packet(uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
}

Packet::Packet(const uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
}

Packet::~Packet(){
    if (this->data != nullptr)
        delete[] this->data;
}

void Packet::setLength(unsigned int len){
    this->length = len;
}

unsigned int Packet::getLength(){
    return this->length;
}

void Packet::setPacketData(uint8_t* data, size_t len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, len);
}

uint8_t* Packet::getPacketData(){
    return this->data;
}
