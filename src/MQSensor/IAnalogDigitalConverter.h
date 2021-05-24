#include <cstdint>

class IAnalogDigitalConverter
{
public:
    virtual uint16_t read() = 0;
};
