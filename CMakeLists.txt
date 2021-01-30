cmake_minimum_required(VERSION 3.17)
project(FuckDWM)

set(CMAKE_CXX_STANDARD 20)
#链接库
link_libraries(psapi.dll)

add_executable(FuckDWM src/main.cpp src/Common.h src/ProcUtils.cpp src/ProcUtils.h src/TimeUtil.h src/TimeUtil.cpp)