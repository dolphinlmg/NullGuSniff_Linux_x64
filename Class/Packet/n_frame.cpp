#include "n_frame.h"

n_Frame::n_Frame() { this->data = nullptr; }

n_Frame::n_Frame(uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
    this->length = len;
}

n_Frame::n_Frame(const uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
    this->length = len;
}

n_Frame::~n_Frame(){
    if (this->data != nullptr)
        delete[] this->data;
}

void n_Frame::setLength(size_t len){
    this->length = len;
}

size_t n_Frame::getLength() const {
    return this->length;
}

void n_Frame::setFrameData(uint8_t* data, size_t len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, len);
}

uint8_t* n_Frame::getFrameData() const {
    return this->data;
}
