#include "ADS1115Support.h"

#include <iostream>

int main()
{
  std::cout << "HELLO" << std::endl;
  ADS1115Device dev;

  // single shot on A0 - +-6.144V
  ADS1115Register readA0SingleConfiguration((uint16_t)0xC180);
  dev.writeData(ADS1115RegisterId::config, readA0SingleConfiguration);
  ADS1115Register reg((uint16_t)0);
  // this is a polling loop ... improve
  int loopCount = 0u;
  while ((reg.number & 0x8000) == 0)
  {
    loopCount++;
    reg = dev.readData();
  }
  auto val = dev.readData(ADS1115RegisterId::conversion);
  std::cout << std::hex << "Result: 0x" << val.number << std::endl;
  std::cout << std::dec << "with: " << loopCount << " polling loops!" << std::endl;
  return 0;
}
