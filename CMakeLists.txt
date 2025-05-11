cmake_minimum_required(VERSION 3.22)

include("cmake/logger.cmake") # import logger module

if(NOT DEFINED TARGET)
    LOG_ERROR("Undefined target.")
    return()
else()
    LOG_INFO("Target: ${TARGET}.")
endif()

set(PROJECT_TARGET ${TARGET})

set(PROJECT_ROOT_DIR            ${CMAKE_SOURCE_DIR})
set(PROJECT_CMAKE_DIR           ${PROJECT_ROOT_DIR}/cmake)
set(PROJECT_SOURCES_DIR         ${PROJECT_ROOT_DIR}/src)
set(PROJECT_LIBRARIES_DIR       ${PROJECT_ROOT_DIR}/libs)
set(PROJECT_TARGET_LIST_DIR     ${PROJECT_ROOT_DIR}/target)
set(PROJECT_TARGET_DIR          ${PROJECT_TARGET_LIST_DIR}/${PROJECT_TARGET})

set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
set(DISABLE_COMPILER_CONF           0)

set(__PROJECT_NAME "TheRush_${TARGET}")
project(${__PROJECT_NAME} VERSION 0.1 LANGUAGES C ASM)

# Define the log level
if (NOT LOG_LEVEL)
    set(LOG_LEVEL INFO)
endif()

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

#[[
#   TODO: add envirnmont check, such as lua, arm-none-eabi-toolchain and so on
#]]

if(NOT EXISTS ${PROJECT_TARGET_DIR})
    LOG_ERROR("Target ${PROJECT_TARGET_DIR} was defined but does not exist.")
    return()
endif()

add_subdirectory("target")
include("${PROJECT_TARGET_DIR}/target.cmake") # get target configurations

include("toolchain/${TARGET_BUILD_TOOLCHAIN}.cmake") # compilers configurations

add_executable(${CMAKE_PROJECT_NAME})

LOG_INFO("${CMAKE_PROJECT_NAME} configure done.")
