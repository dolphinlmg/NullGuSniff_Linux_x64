#ifndef FRAME_H
#define FRAME_H
#include <stdint.h>
#include <cstring>
#include <string>

class Frame
{
public:
    Frame();
    Frame(uint8_t* data, size_t len);
    Frame(const uint8_t* data, size_t len);
    virtual ~Frame();
    void setLength(size_t len);
    size_t getLength();
    void setFrameData(uint8_t* data, size_t len);
    uint8_t* getFrameData();
    virtual std::string what() { return "Frame"; }

private:
    size_t length;
    uint8_t* data;
};

#endif // FRAME_H
