#include "MQSensor.h"

#include "IAnalogDigitalConverter.h"

MQSensor::MQSensor(IAnalogDigitalConverter *analogDigitalConverter) : adc_(analogDigitalConverter)
{
}

uint16_t MQSensor::read()
{
    return this->adc_->read();
}
