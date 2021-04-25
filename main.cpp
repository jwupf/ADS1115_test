#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

class ADS1115Device
{
  // https://cdn-shop.adafruit.com/datasheets/ads1115.pdf
  // 4 16-Bit Register
  // 0 - Conversion Register
  // 1 - ConfigRegister
  // 2 - Lo_thresh
  // 3 - Hi_thresh
private:
  int i2c_device_id;

public:
  ADS1115Device()
  {
    std::cout << "c'tor" << std::endl;
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
    std::cout << "d'tor" << std::endl;
    if (this->i2c_device_id >= 0)
    {
      close(this->i2c_device_id);
    }
  }
  void readData()
  {
    uint8_t readRegisterBuffer[1]{2};
    if (write(this->i2c_device_id, readRegisterBuffer, 1) != 1)
    {
      throw std::runtime_error("Failed to write to the i2c bus.");
    }

    uint8_t readValueBuffer[2]={0,0};
    if (read(this->i2c_device_id, readValueBuffer, 2) != 2)
    {
      throw std::runtime_error("Failed to read from the i2c bus.");
    }
    else
    {
      std::cout<< "1:" << unsigned(readValueBuffer[0]) << " 2:" << unsigned(readValueBuffer[1]) << std::endl;
    }


    // string res;
    // if (read(this->i2c_device_id, buffer, length) != length)
    // {
    //   printf("Failed to read from the i2c bus.\n");
    // }
    // else
    // {
    //   printf("Data read: %s\n", buffer);
    // }
    // return res;
  }
  void writeData()
  {
    // buffer[0] = 0x01; // Register 0-3
    // buffer[1] = 0x02; // Value
    // if (write(this->i2c_device_id, buffer, length) != length)
    // {
    //   printf("Failed to write to the i2c bus.\n");
    // }
  }
};

int main()
{
  std::cout << "HELLO" << std::endl;
  ADS1115Device dev;
  dev.readData();
  return 0;
}
