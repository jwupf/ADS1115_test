#include <cstdint>

class IAnalogDigitalConverter;

class MQSensor
{
private:
    IAnalogDigitalConverter *adc_;

public:
    MQSensor(IAnalogDigitalConverter *analogDigitalConverter);
    uint16_t read();
};
