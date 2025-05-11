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

include("cmake/utils.cmake") # import utils module

if(NOT DEFINED TARGET)
    LOG_ERROR("Undefined target.")
    return()
else()
    LOG_INFO("Target: ${TARGET}.")
endif()

set(PROJECT_TARGET ${TARGET})
set(__PROJECT_NAME "TheRush_${TARGET}")

set(PROJECT_ROOT_PATH            ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCES_PATH         ${PROJECT_ROOT_PATH}/src)
set(PROJECT_LIBRARIES_PATH       ${PROJECT_ROOT_PATH}/libs)
set(PROJECT_TARGET_PATH          ${PROJECT_ROOT_PATH}/target)
set(PROJECT_TARGET_CONFIG_DIR    ${PROJECT_TARGET_PATH}/${PROJECT_TARGET})

set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
set(DISABLE_COMPILER_CONF           0)

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

if(NOT EXISTS ${PROJECT_TARGET_CONFIG_DIR})
    LOG_ERROR("Target ${PROJECT_TARGET_CONFIG_DIR} was defined but does not exist.")
    return()
endif()

add_subdirectory("target")
include("toolchain/${TARGET_BUILD_TOOLCHAIN}.cmake") # compilers configurations
include("${PROJECT_TARGET_CONFIG_DIR}/target.cmake") # get target configurations

project(${__PROJECT_NAME} VERSION 0.1 LANGUAGES C ASM)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory("libs")
add_subdirectory("src")

LOG_INFO("${CMAKE_PROJECT_NAME} configure done.")
