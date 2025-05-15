#[[
# This file is a part of ThetaRush.
#
# ThetaRush is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ThetaRush is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.
#
# If not, see <https://www.gnu.org/licenses/>.
]]

cmake_minimum_required(VERSION 3.22)

include("cmake/debug.cmake")

if(NOT DEFINED TARGET)
    LOG_ERROR("Undefined target.")
    return()
else()
    LOG_INFO("Target: ${TARGET}.")
endif()

set(PROJECT_TARGET      ${TARGET})
set(PROJECT_NAME        ThetaRush_${PROJECT_TARGET})

set(PROJECT_SOURCE_PATH         ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_LIBRARIES_PATH      ${PROJECT_SOURCE_PATH}/libs)
set(PROJECT_SOURCES_PATH        ${PROJECT_SOURCE_PATH}/src)
set(PROJECT_TARGET_PATH         ${PROJECT_SOURCE_PATH}/target)
set(PROJECT_TARGET_CONFIG_PATH  ${PROJECT_TARGET_PATH}/${PROJECT_TARGET})

set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Define the log level
if (NOT DEFINED LOG_LEVEL)
    set(LOG_LEVEL DEBUG)
endif()

# Define the build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

include("${PROJECT_TARGET_CONFIG_PATH}/target.cmake")

if(NOT DEFINED TARGET_MCU OR NOT DEFINED TARGET_MCU_SERIES OR NOT DEFINED TARGET_BUILD_TOOLCHAIN)
    LOG_ERROR("Missing defination(s) in ${PROJECT_TARGET_DIR}/target.cmake.")
    return()
else()
    LOG_INFO("Target mcu \"${TARGET_MCU}\" belong to series \"${TARGET_MCU_SERIES}\", using toolchain \"${TARGET_BUILD_TOOLCHAIN}\".")
endif()

include("toolchain/${TARGET_BUILD_TOOLCHAIN}.cmake") # compilers configurations

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES C ASM)

add_executable(${PROJECT_NAME})

add_subdirectory("target")
add_subdirectory("libs")
add_subdirectory("src")

LOG_INFO("${CMAKE_PROJECT_NAME} configure done.")