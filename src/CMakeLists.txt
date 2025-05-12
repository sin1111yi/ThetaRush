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

set(PROJECT_SOURCES_IMPL_PATH ${PROJECT_SOURCES_PATH}/impl)
set(PROJECT_SOURCES_MAIN_PATH ${PROJECT_SOURCES_PATH}/main)
set(PROJECT_SOURCES_UTILS_PATH ${PROJECT_SOURCES_PATH}/utils)

set(TARGET_PLATFORM_LINKER_PATH ${TARGET_PLATFORM_PATH}/link)
set(TARGET_PLATFORM_STARTUP_PATH ${TARGET_PLATFORM_PATH}/startup)
set(TARGET_PLATFORM_SRC_PATH ${TARGET_PLATFORM_PATH}/platform)

set(TARGET_PLATFORM_LINKER_FILE "")
set(TARGET_PLATFORM_STARTUP_FILE "")

string(TOLOWER ${TARGET_MCU} _TARGET_MCU_)
set(_TARGET_MCU_ ${_TARGET_MCU_} CACHE INTERNAL "_TARGET_MCU_")

if(EXISTS ${TARGET_PLATFORM_LINKER_PATH}/${_TARGET_MCU_}_flash.ld)
    set(TARGET_PLATFORM_LINKER_FILE ${TARGET_PLATFORM_LINKER_PATH}/${_TARGET_MCU_}_flash.ld)
    LOG_INFO("Found target platform link file: ${TARGET_PLATFORM_LINKER_FILE}.")
else()
    LOG_ERROR("Can't find target platform ${_TARGET_MCU_} linker script \"${_TARGET_MCU_}_flash.ld\".")
    return()
endif()

if(EXISTS ${TARGET_PLATFORM_STARTUP_PATH}/startup_${_TARGET_MCU_}.s)
    set(TARGET_PLATFORM_STARTUP_FILE ${TARGET_PLATFORM_STARTUP_PATH}/startup_${_TARGET_MCU_}.s)
    LOG_INFO("Found target platform startup file: ${TARGET_PLATFORM_STARTUP_PATH}/startup_${_TARGET_MCU_}.s.")
else()
    LOG_ERROR("Can't find target platform ${_TARGET_MCU_} startup file \"starup_${_TARGET_MCU_}.s\".")
    return()
endif()

set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${TARGET_PLATFORM_LINKER_FILE}\"")

file(GLOB
    PROJECT_SOURCES_PLATFORM_FILES
    "${TARGET_PLATFORM_SRC_PATH}/*.c"
    "${TARGET_PLATFORM_SRC_PATH}/periph/*.c"
    "${TARGET_PLATFORM_SRC_PATH}/interrupt/*.c"
    "${TARGET_PLATFORM_SYSTEM_PATH}/*.c"
)

file(GLOB_RECURSE
    PROJECT_SOURCES_IMPL_FILES
    "${PROJECT_SOURCES_IMPL_PATH}/*.c"
)

file(GLOB_RECURSE
    PROJECT_SOURCES_MAIN_FIELS
    "${PROJECT_SOURCES_MAIN_PATH}/*.c"
)

file(GLOB_RECURSE
    PROJECT_SOURCES_UTILS_FILES
    "${PROJECT_SOURCES_UTILS_PATH}/*.c"
)

DEBUG_DUMP_FILES(
    FILE_LIST
    ${PROJECT_SOURCES_PLATFORM_FILES}
    ${PROJECT_SOURCES_IMPL_FILES}
    ${PROJECT_SOURCES_MAIN_FIELS}
    ${PROJECT_SOURCES_UTILS_FILES}

    ${TARGET_PLATFORM_STARTUP_FILE}
    INFO "Platfrom ${TARGET_MCU_PLATFORM} Sources")

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCES_PLATFORM_FILES}
    ${PROJECT_SOURCES_IMPL_FILES}
    ${PROJECT_SOURCES_MAIN_FIELS}
    ${PROJECT_SOURCES_UTILS_FILES}

    ${TARGET_PLATFORM_STARTUP_FILE}
    ${TARGET_PLATFORM_SYSTEM_PATH}
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCES_PATH}
    ${PROJECT_SOURCES_MAIN_PATH}
    ${PROJECT_SOURCES_UTILS_PATH}
    ${TARGET_PLATFORM_PATH}
    ${PROJECT_TARGET_CONFIG_PATH}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
    ${TARGET_DRV_LIBRARY}
)