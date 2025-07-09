cmake_minimum_required(VERSION 3.10)
project(test)

# C++标准配置（关键修改）
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 构建类型配置
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 编译选项配置
set(CMAKE_CXX_FLAGS_DEBUG " -Wall -Werror -g -O0 ")
set(CMAKE_C_FLAGS_DEBUG " -Wall -Werror -g -O0 ")
set(CMAKE_CXX_FLAGS_RELEASE " -Wall -Werror -O3 ")
set(CMAKE_C_FLAGS_RELEASE " -Wall -Werror -O3 ")

# OpenCV配置
find_package(OpenCV REQUIRED)

# 头文件路径
include_directories(
    /usr/include/dnn
    ${OpenCV_INCLUDE_DIRS}
)

# 库文件路径
link_directories(
    /usr/lib
    /usr/local/lib
)

# 可执行文件
add_executable(main main.cpp)

# 链接库
target_link_libraries(main
    spcdev
    jpeg
    dnn
    ${OpenCV_LIBS}
    pthread
    rt
    dl
)

# 安装配置
install(TARGETS main RUNTIME DESTINATION bin)