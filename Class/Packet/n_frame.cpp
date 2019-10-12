#include "n_frame.h"

// default constructor setting data to nullptr
n_Frame::n_Frame() { this->data = nullptr; }

// constructor with uint8_t*
n_Frame::n_Frame(uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
    this->length = len;
}

// constructor with const uint8_t*
n_Frame::n_Frame(const uint8_t* data, size_t len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, len);
    this->length = len;
}

//destructor: delete[] data
n_Frame::~n_Frame(){
    if (this->data != nullptr)
        delete[] this->data;
}

// set length of packet
void n_Frame::setLength(size_t len){
    this->length = len;
}

// return length of packet
size_t n_Frame::getLength() const {
    return this->length;
}

// set data with uint8_t*
void n_Frame::setFrameData(uint8_t* data, size_t len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, len);
}

// set data with const uint8_t*
void n_Frame::setFrameData(const uint8_t* data, size_t len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, len);
}

// return data
uint8_t* n_Frame::getFrameData() const {
    return this->data;
}
