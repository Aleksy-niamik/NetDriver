# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)



# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
#set(PICO_SDK_PATH "/usr/share/pico-sdk")

# Pull in Pico SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)


project(NetDriver C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(NetDriver
    main.cpp
    imgs.cpp
    net/ColorSpaces.cpp
    effects.cpp
)

pico_generate_pio_header(NetDriver ${CMAKE_CURRENT_LIST_DIR}/net/WS2812b_2017.pio)

pico_set_program_name(NetDriver "NetDriver")
pico_set_program_version(NetDriver "1.0")

pico_enable_stdio_uart(NetDriver 1)
pico_enable_stdio_usb(NetDriver 1)

# Add the standard library to the build
target_link_libraries(NetDriver 
        pico_stdlib
        pico_multicore
)

# Add any user requested libraries
target_link_libraries(NetDriver
        hardware_pio
)

pico_add_extra_outputs(NetDriver)
