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

set(LIB_TARGET_DEF_INTERFACE libinterface_${TARGET}_defs)

if(NOT EXISTS ${PROJECT_TARGET_CONFIG_DIR}/target.lua)
    LOG_ERROR("Target defination file does not exist.")
    return()
endif()

# clean old files before generate new files
execute_process(
    COMMAND lua target_config_gen.lua --clean ${TARGET}
    WORKING_DIRECTORY ${PROJECT_TARGET_PATH}
    RESULT_VARIABLE CLEAN_RESULT
)

# call target_config_gen.lua to generate target.h and target.lua
execute_process(
    COMMAND lua target_config_gen.lua --target ${TARGET}
    WORKING_DIRECTORY ${PROJECT_TARGET_PATH}
    RESULT_VARIABLE GEN_RESULT
)

if(NOT EXISTS ${PROJECT_TARGET_CONFIG_DIR}/target.h OR NOT EXISTS ${PROJECT_TARGET_CONFIG_DIR}/target.cmake)
    LOG_ERROR("Run target/generate.lua with target ${PROJECT_TARGET} failed.")
    return()
endif()

include("${PROJECT_TARGET_CONFIG_DIR}/target.cmake")

if(NOT DEFINED TARGET_MCU OR NOT DEFINED TARGET_MCU_SERIES OR NOT DEFINED TARGET_BUILD_TOOLCHAIN)
    LOG_ERROR("Missing defination(s) in ${PROJECT_TARGET_CONFIG_DIR}/target.cmake.")
    return()
else()
    LOG_INFO("Target mcu \"${TARGET_MCU}\" belong to series \"${TARGET_MCU_SERIES}\", using toolchain \"${TARGET_BUILD_TOOLCHAIN}\".")
endif()

if(${TARGET_MCU_SERIES} STREQUAL "STM32H7")
    set(TAREGT_MCU_FLAGS
        USE_PWR_LDO_SUPPLY
        USE_HAL_DRIVER
        ${TARGET_MCU}
        CACHE INTERNAL "Target mcu compile flags.")
    set(TARGET_MCU_VENDOR ST PARENT_SCOPE) 
    set(TARGET_MCU_PLATFORM STM32 PARENT_SCOPE)
endif()

LOG_INFO("Add Library ${LIB_TARGET_DEF_INTERFACE}")
add_library(${LIB_TARGET_DEF_INTERFACE} INTERFACE)
target_include_directories(${LIB_TARGET_DEF_INTERFACE}
    INTERFACE
    ${PROJECT_TARGET_CONFIG_DIR}
)
target_compile_definitions(${LIB_TARGET_DEF_INTERFACE}
    INTERFACE
    ${TAREGT_MCU_FLAGS}
)