#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

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

struct ExtADS1115Register {  
  uint8_t bytes[2];    
};

union ADS1115Register {
  uint16_t number;
  uint8_t bytes[2];  
  ADS1115Register(){    
    number = 0;
  }
  ADS1115Register(const ExtADS1115Register remote){
    bytes[0] = remote.bytes[1];
    bytes[1] = remote.bytes[0];  
  }
  ADS1115Register(const uint16_t n){
    number = n;
  }
  ADS1115Register(const uint8_t data[2]){
    bytes[0] = data[0];
    bytes[1] = data[1];
  }
};

class ADS1115Device
{
private:
  const uint8_t bytesPerPointerRegister = 1;
  const uint8_t bytesPerRegister = 2;
  const uint8_t bytesPerWrite = bytesPerPointerRegister + bytesPerRegister;
  int i2c_device_id;

public:
  ADS1115Device()
  {
    this->i2c_device_id = open("/dev/i2c-1", O_RDWR);
    if (this->i2c_device_id < 0)
    {
      throw std::runtime_error("could not open i2c device");
    }
    if (ioctl(this->i2c_device_id, I2C_SLAVE, 0x48) < 0)
    {
      throw std::runtime_error("Failed to acquire bus access and/or talk to slave.");
    }
  }

  ~ADS1115Device()
  {
    if (this->i2c_device_id >= 0)
    {
      close(this->i2c_device_id);
    }
  }

  ADS1115Register readData(ADS1115RegisterId targetRegister) const
  {
    uint8_t readRegisterBuffer[bytesPerPointerRegister]{targetRegister};
    if (write(this->i2c_device_id, readRegisterBuffer, bytesPerPointerRegister) != bytesPerPointerRegister)
    {
      throw std::runtime_error("Failed to write to the i2c bus.");
    }
    return readLastConfiguration();
  }
  
  ADS1115Register readLastConfiguration() const
  {
    ExtADS1115Register data;
    if (read(this->i2c_device_id, data.bytes, bytesPerRegister) != bytesPerRegister)
    {
      throw std::runtime_error("Failed to read from the i2c bus.");
    }

    return ADS1115Register(data);
  }

  void writeData(ADS1115RegisterId targetRegister, const ADS1115Register& data) const
  {
    uint8_t writeBuffer[bytesPerWrite] = {targetRegister, data.bytes[1], data.bytes[0]};
    if (write(this->i2c_device_id, writeBuffer, bytesPerWrite) != bytesPerWrite)
    {
      throw std::runtime_error("Failed to write to the i2c bus.");
    }
  }
};

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
  while((reg.number & 0x8000) == 0){
    loopCount++;
    reg = dev.readLastConfiguration();
  }
  auto val = dev.readData(ADS1115RegisterId::conversion);
  std::cout << std::hex << "Result: 0x" << val.number << std::endl;
  std::cout << std::dec << "with: " << loopCount <<" polling loops!" << std::endl;
  return 0;
}
