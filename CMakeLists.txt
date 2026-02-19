cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME ShroomShed_MKII)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

add_subdirectory(lvgl)


# Create EEZ UI library
file(GLOB EEZ_UI_SOURCES "Lib/EEZ/src/ui/*.c")
add_library(eez_ui STATIC ${EEZ_UI_SOURCES})
target_include_directories(eez_ui PUBLIC 
    Lib/EEZ/src/ui
    Lib/EEZ/src/images
    lvgl/src
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
    lvgl
)

# Add sources to executable
file(GLOB SHT31_SOURCES "Lib/sht31/src/*.c")
file (GLOB USB_SOURCES "Lib/USB/Core/Src/*.c" "Lib/USB/Class/CDC/Src/*.c")


target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Lib/ili9341/ili9341.c
    Lib/ili9341/ili9341_touch.c
    Core/Src/display_manager.c
    Core/Src/sensors.c
    Lib/SCD40/SCD40_driver.c
    Lib/SCD40/SCD40_API.c
    ${SHT31_SOURCES}
    ${USB_SOURCES}
    
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Core/Inc
    Lib/USB/Class/CDC/Inc
    Lib/USB/Core/Inc
    Lib/ili9341
    Lib/sht31/src
    Lib/SCD40
    lvgl
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    lvgl
    eez_ui

    # Add user defined libraries
)
