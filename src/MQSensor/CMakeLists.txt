add_library(mqsensor MQSensor.cpp)

target_include_directories(mqsensor PUBLIC
                        "${PROJECT_SOURCE_DIR}"
                        )
