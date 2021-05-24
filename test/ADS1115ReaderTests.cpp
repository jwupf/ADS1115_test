#include <gtest/gtest.h>

#include "MQSensor.h"
#include "IAnalogDigitalConverter.h"

class FakeADConverter : public IAnalogDigitalConverter {
  uint16_t val_;
  public:
  FakeADConverter(uint16_t val) : val_(val){

  }

  uint16_t read(){
    return this->val_;
  }
};

TEST(MQXXXTest, GetValue) {
  // arrange
  uint16_t expectedValue = 0x1578u;
  FakeADConverter adc(expectedValue);
  MQSensor sensor((IAnalogDigitalConverter*)&adc);

  // act
  uint16_t sensorValue = sensor.read();

  // assert
  ASSERT_EQ(sensorValue, expectedValue);
}
