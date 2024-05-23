cmake_minimum_required(VERSION 3.12)

#Pull in pico sdk (before project)
include(pico_sdk_import.cmake)

project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

#Initialize the sdk
pico_sdk_init()

#Add the include directory for header files
include_directories(include)

add_executable(main
	src/main.c src/ssd1306.c
	)

#Pull in pico_stdlib
target_link_libraries(main pico_stdlib hardware_i2c)

#Create map/bin/hex file etc
pico_add_extra_outputs(main)
