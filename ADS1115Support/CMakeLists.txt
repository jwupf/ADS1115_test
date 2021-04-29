add_library(ADS1115Support ADS1115Support.cpp)

target_link_libraries(ADS1115Support PUBLIC i2c)