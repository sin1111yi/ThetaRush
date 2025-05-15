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

if(NOT EXISTS ${PROJECT_TARGET_CONFIG_PATH}/target.h OR NOT EXISTS ${PROJECT_TARGET_CONFIG_PATH}/target.cmake)
    LOG_ERROR("Didn't detect target config files for target ${PROJECT_TARGET}. Please run \"target_config_gen.lua\".")
    return()
endif()

if(${TARGET_MCU_SERIES} STREQUAL "STM32H7")
    set(TAREGT_MCU_FLAGS
        USE_PWR_LDO_SUPPLY
        USE_HAL_DRIVER
        ${TARGET_MCU}
        CACHE INTERNAL "Target mcu compile flags.")
    set(TARGET_MCU_VENDOR ST CACHE INTERNAL "Target MCU Vendor")
    set(TARGET_MCU_PLATFORM STM32 CACHE INTERNAL "Target MCU Platform")
endif()

set(PROJECT_TARGET_PLATFORM_PATH
    ${PROJECT_SOURCES_PATH}/platform/${TARGET_MCU_PLATFORM}
    CACHE INTERNAL
    "Target Platform Path"
)