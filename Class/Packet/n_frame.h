#ifndef FRAME_H
#define FRAME_H
#include <stdint.h>
#include <cstring>
#include <string>

class n_Frame
{
public:
    n_Frame();
    n_Frame(uint8_t* data, int len);
    n_Frame(const uint8_t* data, int len);
    virtual ~n_Frame();
    void setLength(int len);
    int getLength() const ;
    void setFrameData(uint8_t* data, int len);
    void setFrameData(const uint8_t* data, int len);
    uint8_t* getFrameData() const ;
    virtual std::string what() const { return "Frame"; } //return name of class

private:
    int length;
    uint8_t* data;
};

#endif // FRAME_H
