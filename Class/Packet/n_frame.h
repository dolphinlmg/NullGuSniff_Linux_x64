#ifndef FRAME_H
#define FRAME_H
#include <stdint.h>
#include <cstring>
#include <string>

class n_Frame
{
public:
    n_Frame();
    n_Frame(uint8_t* data, size_t len);
    n_Frame(const uint8_t* data, size_t len);
    virtual ~n_Frame();
    void setLength(size_t len);
    size_t getLength() const ;
    void setFrameData(uint8_t* data, size_t len);
    void setFrameData(const uint8_t* data, size_t len);
    uint8_t* getFrameData() const ;
    virtual std::string what() const { return "Frame"; } //return name of class

private:
    size_t length;
    uint8_t* data;
};

#endif // FRAME_H
