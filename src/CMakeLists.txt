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

string(TOLOWER ${TARGET_MCU}_flash.ld _PROJECT_TARGET_LINK_FILE)
set(PROJECT_TARGET_LINK_FILE ${PROJECT_TARGET_PLATFORM_PATH}/link/${_PROJECT_TARGET_LINK_FILE})

string(TOLOWER startup_${TARGET_MCU}.s _PROJECT_TAGRET_STARTUP_FILE)
set(PROJECT_TAGRET_STARTUP_FILE ${PROJECT_TARGET_PLATFORM_PATH}/startup/${_PROJECT_TAGRET_STARTUP_FILE})

if(NOT EXISTS ${PROJECT_TARGET_LINK_FILE})
    LOG_ERROR("Missing file ${_PROJECT_TARGET_LINK_FILE}")
    return()
else()
    LOG_DEBUG("Found link file: ${PROJECT_TARGET_LINK_FILE}")
endif()

if(NOT EXISTS ${PROJECT_TAGRET_STARTUP_FILE})
    LOG_ERROR("Missing file ${_PROJECT_TAGRET_STARTUP_FILE}")
    return()
else()
    LOG_DEBUG("Found startup file: ${PROJECT_TAGRET_STARTUP_FILE}")
endif()

set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${PROJECT_TARGET_LINK_FILE}\"" PARENT_SCOPE)

file(GLOB_RECURSE
    ThetaRush_main_sources
    "${PROJECT_SOURCES_PATH}/main/*.c"
)

DEBUG_DUMP_FILES(
    FILE_LIST
    ${ThetaRush_main_sources}
    INFO
    "ThetaRush Main Sources:"
)

file(GLOB_RECURSE
    ThetaRush_platfrom_sources
    "${PROJECT_TARGET_PLATFORM_PATH}/platform/*.c"
)

DEBUG_DUMP_FILES(
    FILE_LIST
    ${ThetaRush_platfrom_sources}
    INFO
    "ThetaRush Platfrom Sources:"
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${ThetaRush_main_sources}
    ${ThetaRush_platfrom_sources}
    ${PROJECT_TAGRET_STARTUP_FILE}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    "${PROJECT_TARGET_CONFIG_PATH}"
    "${PROJECT_TARGET_PLATFORM_PATH}"
    "${PROJECT_SOURCES_PATH}/main"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${TARGET_DRV_LIBRARY}
)