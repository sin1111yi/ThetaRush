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

LOG_INFO("Begin to configure drivers library with target ${PROJECT_TARGET}.")

set(TARGET_DRV_INTERFACE libinterface_${TARGET_MCU_SERIES}_drv CACHE INTERNAL "Target Drivers Interface")
set(TARGET_DRV_LIBRARY libobject_${TARGET_MCU_SERIES}_drv CACHE INTERNAL "Target Drivers Library")

set(TARGET_DRIVERS_PATH ${PROJECT_LIBRARIES_PATH}/drivers)
set(TARGET_CMSIS_PATH ${PROJECT_LIBRARIES_PATH}/drivers/CMSIS)
set(TARGET_MIDWARES_PATH ${PROJECT_LIBRARIES_PATH}/middlewares)
set(TARGET_DRIVER_PATH "")

if(${TARGET_MCU_VENDOR} STREQUAL "ST")
    set(TARGET_CMSIS_DEVICE_PATH ${TARGET_CMSIS_PATH}/Device/${TARGET_MCU_VENDOR}/${TARGET_MCU_SERIES}xx)
endif()

if(NOT EXISTS ${TARGET_CMSIS_DEVICE_PATH})
    LOG_ERROR("CMSIS device path doesn't exist for ${PROJECT_TARGET}, MCU \"${TARGET_MCU_SERIES}xx\".")
    return()
else()
    set(TARGET_CMSIS_DEVICE_INC_PATH ${TARGET_CMSIS_DEVICE_PATH}/Include)
    LOG_INFO("Get CMSIS device path for ${PROJECT_TARGET},  \"${TARGET_CMSIS_DEVICE_PATH}\".")
endif()

if(EXISTS ${TARGET_CMSIS_PATH}/Include)
    set(TAGRET_CMSIS_INC_PATH ${TARGET_CMSIS_PATH}/Include)
else()
    LOG_ERROR("Missing path \"${TARGET_CMSIS_PATH}/Include\".")
    return()
endif()

file(GLOB ALL_DRIVER_LIBS
    LIST_DIRECTORIES true
    "${TARGET_DRIVERS_PATH}/*"
)
set(FLAG_GET_TARGET_DRIVERS 0)

foreach(DIR IN LISTS ALL_DRIVER_LIBS)
    get_filename_component(DIR_NAME "${DIR}" NAME)
    if(DIR_NAME MATCHES "${TARGET_MCU_SERIES}.*Driver" AND IS_DIRECTORY "${DIR}")
        set(TARGET_DRIVER_PATH "${DIR}")
        set(FLAG_GET_TARGET_DRIVERS 1)
        break()
    endif()
endforeach()

if(FLAG_GET_TARGET_DRIVERS EQUAL 0)
    LOG_ERROR("Drivers for \"${TARGET_MCU_SERIES}\" doesn't exits.")
    return()
endif()

LOG_INFO("Get target drivers at ${TARGET_DRIVER_PATH}.")
set(TARGET_DRIVER_INC_PATH ${TARGET_DRIVER_PATH}/Inc)
set(TARGET_DRIVER_LEGACY_INC_PATH "")
if(EXISTS ${TARGET_DRIVER_PATH}/Inc/Legacy)
    set(TARGET_DRIVER_LEGACY_INC_PATH ${TARGET_DRIVER_PATH}/Inc/Legacy)
endif()
set(TARGET_DRIVER_SRC_PATH ${TARGET_DRIVER_PATH}/Src)

LOG_INFO("Drivers' includes at \"${TARGET_DRIVER_INC_PATH}\", sources at \"${TARGET_DRIVER_SRC_PATH}\"")

set(TARGET_DRV_INTERFACE_INC_PATH
    ${PROJECT_TARGET_PLATFORM_PATH}/platform/system/${TARGET_MCU_SERIES}xx

    ${TARGET_DRIVER_INC_PATH}
    ${TARGET_DRIVER_LEGACY_INC_PATH}
    ${TARGET_CMSIS_DEVICE_INC_PATH}
    ${TAGRET_CMSIS_INC_PATH}
)

LOG_INFO("Add library ${TARGET_DRV_INTERFACE}.")
add_library(${TARGET_DRV_INTERFACE} INTERFACE)
target_include_directories(${TARGET_DRV_INTERFACE}
    INTERFACE
    ${TARGET_DRV_INTERFACE_INC_PATH}
)
target_compile_definitions(${TARGET_DRV_INTERFACE}
    INTERFACE
    ${TAREGT_MCU_FLAGS} # Defined in ${PROJECT_ROOT_PATH}/target/CMakeLists.txt
)

DEBUG_DUMP_FILES(
    FILE_LIST ${TARGET_DRV_INTERFACE_INC_PATH} 
    INFO "Library ${TARGET_MCU_SERIES}xx Includes")

file(GLOB __TARGET_DRV_SRC_FILES LIST_DIRECTORIES false CONFIGURE_DEPENDS "${TARGET_DRIVER_SRC_PATH}/*.c")
# Filter out template files
set(TARGET_DRV_SRC_FILES "")
foreach(__FILE IN LISTS __TARGET_DRV_SRC_FILES)
    get_filename_component(FILENAME ${__FILE} NAME)
    if(NOT FILENAME MATCHES "template")
        list(APPEND TARGET_DRV_SRC_FILES ${__FILE})
    endif()
endforeach()

set(TARGET_DRV_LIBRARY_SRC_FILES
    ${TARGET_DRV_SRC_FILES}
)

DEBUG_DUMP_FILES(
    FILE_LIST ${TARGET_DRV_LIBRARY_SRC_FILES} 
    INFO "Library ${TARGET_MCU_SERIES}xx Sources")

LOG_INFO("Add Library ${TARGET_DRV_LIBRARY}.")
add_library(${TARGET_DRV_LIBRARY} OBJECT)
target_sources(${TARGET_DRV_LIBRARY}
    PRIVATE
    ${TARGET_DRV_LIBRARY_SRC_FILES}
)
target_link_libraries(${TARGET_DRV_LIBRARY}
    PUBLIC
    ${TARGET_DRV_INTERFACE}
)
