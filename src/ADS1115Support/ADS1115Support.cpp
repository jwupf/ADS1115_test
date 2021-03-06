#include "ADS1115Support.h"

#include <iostream>
// next both are needed for strerro/errno interaction
#include <cerrno>
#include <cstring>

#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include <thread>

using namespace std::chrono_literals;

ADS1115Register::ADS1115Register()
{
    this->number = 0;
}

ADS1115Register::ADS1115Register(const ExtADS1115Register remote)
{
    this->bytes[0] = remote.bytes[1];
    this->bytes[1] = remote.bytes[0];
}

ADS1115Register::ADS1115Register(const uint16_t n)
{
    this->number = n;
}

ADS1115Register::ADS1115Register(const uint8_t data[2])
{
    this->bytes[0] = data[0];
    this->bytes[1] = data[1];
}

ADS1115Device::ADS1115Device()
{
    this->i2c_device_id = open("/dev/i2c-1", O_RDWR);
    if (this->i2c_device_id < 0)
    {
        std::cout << "access to i2c failed: " << std::strerror(errno) << '\n';
        throw std::runtime_error("could not open i2c device");
    }

    if (ioctl(this->i2c_device_id, I2C_SLAVE, 0x48) < 0)
    {
        std::cout << "#### access to i2c failed: " << std::strerror(errno) << '\n';
        if (ioctl(this->i2c_device_id, I2C_SLAVE, 0x48) < 0)
        {
            std::cout << "access to i2c failed: " << std::strerror(errno) << '\n';
            throw std::runtime_error("Failed to acquire bus access and/or talk to slave.");
        }
    }
}

ADS1115Device::~ADS1115Device()
{
    if (this->i2c_device_id >= 0)
    {
        close(this->i2c_device_id);
    }
}

ADS1115Register ADS1115Device::readData(ADS1115RegisterId targetRegister) const
{
    uint8_t readRegisterBuffer[bytesPerPointerRegister]{targetRegister};
    auto writtenBytes = write(this->i2c_device_id, readRegisterBuffer, bytesPerPointerRegister);
    if (writtenBytes != bytesPerPointerRegister)
    {
        std::cout << "#### access to i2c failed: " << std::strerror(errno) << '\n';
        writtenBytes = write(this->i2c_device_id, readRegisterBuffer, bytesPerPointerRegister);
        if (writtenBytes != bytesPerPointerRegister)
        {
            std::cout << "access to i2c failed: " << std::strerror(errno) << '\n';
            throw std::runtime_error("Failed to write to the i2c bus.");
        }
    }
    return readData();
}

ADS1115Register ADS1115Device::readData() const
{
    ExtADS1115Register data;
    auto readBytes = read(this->i2c_device_id, data.bytes, bytesPerRegister);
    if (readBytes != bytesPerRegister)
    {
        std::cout << "#### access to i2c failed: " << std::strerror(errno) << '\n';
        readBytes = read(this->i2c_device_id, data.bytes, bytesPerRegister);
        if (readBytes != bytesPerRegister)
        {
            std::cout << "access to i2c failed: " << std::strerror(errno) << '\n';
            throw std::runtime_error("Failed to read expected number of bytes from the i2c bus.");
        }
    }

    return ADS1115Register(data);
}

void ADS1115Device::writeData(ADS1115RegisterId targetRegister, const ADS1115Register &data) const
{
    uint8_t writeBuffer[bytesPerWrite] = {targetRegister, data.bytes[1], data.bytes[0]};
    if (write(this->i2c_device_id, writeBuffer, bytesPerWrite) != bytesPerWrite)
    {
        std::cout << "#### access to i2c failed: " << std::strerror(errno) << '\n';
        if (write(this->i2c_device_id, writeBuffer, bytesPerWrite) != bytesPerWrite)
        {
            std::cout << "access to i2c failed: " << std::strerror(errno) << '\n';
            throw std::runtime_error("Failed to write to the i2c bus.");
        }
    }
}