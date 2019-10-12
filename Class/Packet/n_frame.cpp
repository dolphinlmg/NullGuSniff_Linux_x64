#include "n_frame.h"

// default constructor setting data to nullptr
n_Frame::n_Frame() { this->data = nullptr; }

// constructor with uint8_t*
n_Frame::n_Frame(uint8_t* data, int len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, static_cast<size_t>(len));
    this->length = len;
}

// constructor with const uint8_t*
n_Frame::n_Frame(const uint8_t* data, int len) {
    this->data = new uint8_t [len];
    if (this->data != nullptr)
        memcpy(this->data, data, static_cast<size_t>(len));
    this->length = len;
}

//destructor: delete[] data
n_Frame::~n_Frame(){
    if (this->data != nullptr)
        delete[] this->data;
}

// set length of packet
void n_Frame::setLength(int len){
    this->length = len;
}

// return length of packet
int n_Frame::getLength() const {
    return this->length;
}

// set data with uint8_t*
void n_Frame::setFrameData(uint8_t* data, int len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, static_cast<size_t>(len));
}

// set data with const uint8_t*
void n_Frame::setFrameData(const uint8_t* data, int len){
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new uint8_t [len];
    memcpy(this->data, data, static_cast<size_t>(len));
}

// return data
uint8_t* n_Frame::getFrameData() const {
    return this->data;
}
