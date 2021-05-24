add_executable(ADS1115ReaderTests ADS1115ReaderTests.cpp)

target_link_libraries(ADS1115ReaderTests PUBLIC gtest_main mqsensor)

target_include_directories(ADS1115ReaderTests PUBLIC
                        "${PROJECT_SOURCE_DIR}/src/MQSensor"                        
                        )

gtest_discover_tests(ADS1115ReaderTests)
