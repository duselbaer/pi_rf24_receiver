project(TempServer)
cmake_minimum_required(VERSION 2.8)

# enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

add_subdirectory(RF24)

include_directories(
  "RF24/include"
)

add_executable(NRF24_Receiver
  main.cpp
)

target_link_libraries(NRF24_Receiver
  bcm2835
)
