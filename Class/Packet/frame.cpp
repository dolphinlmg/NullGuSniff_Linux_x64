#include "frame.h"

Frame::Frame() { this->data = nullptr; }

Frame::Frame(uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
    this->length = len;
}

Frame::Frame(const uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
    this->length = len;
}

Frame::~Frame(){
    if (this->data != nullptr)
        delete[] this->data;
}

void Frame::setLength(size_t len){
    this->length = len;
}

size_t Frame::getLength() const {
    return this->length;
}

void Frame::setFrameData(uint8_t* data, size_t len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, len);
}

uint8_t* Frame::getFrameData() const {
    return this->data;
}
