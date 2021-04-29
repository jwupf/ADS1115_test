#pragma once

#include <cstdint>

enum ADS1115RegisterId : uint8_t
{
  // https://cdn-shop.adafruit.com/datasheets/ads1115.pdf
  // 4 16-Bit Register
  // 0 - Conversion Register
  // 1 - ConfigRegister
  // 2 - Lo_thresh
  // 3 - Hi_thresh
  conversion = 0,
  config = 1,
  loTresh = 2,
  hiTresh = 3
};

struct ExtADS1115Register
{
  uint8_t bytes[2];
};

union ADS1115Register
{
  uint16_t number;
  uint8_t bytes[2];
  ADS1115Register();
  ADS1115Register(const ExtADS1115Register remote);
  ADS1115Register(const uint16_t n);
  ADS1115Register(const uint8_t data[2]);
};

class ADS1115Device
{
private:
  const uint8_t bytesPerPointerRegister = 1;
  const uint8_t bytesPerRegister = 2;
  const uint8_t bytesPerWrite = bytesPerPointerRegister + bytesPerRegister;
  int i2c_device_id;

public:
  ADS1115Device();

  ~ADS1115Device();

  ADS1115Register readData(ADS1115RegisterId targetRegister) const;

  ADS1115Register readData() const;

  void writeData(ADS1115RegisterId targetRegister, const ADS1115Register &data) const;
};
