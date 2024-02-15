cmake_minimum_required(VERSION 3.10)
project(checktronbalance)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(generateAddress)

include_directories(generateAddress/include)
include_directories(nlohmann)

add_executable(checktronbalance main.cpp)
target_link_libraries(checktronbalance pthread curl bitaddress)
