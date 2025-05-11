cmake_minimum_required(VERSION 3.22)
project(GENERATE_TARGET_DEFINATION VERSION 1.0)

set(LIB_TARGET_DEF_INTERFACE libinterface_${PROJECT_NAME}_defs)

if(NOT EXISTS ${PROJECT_TARGET_DIR}/target.lua)
    LOG_ERROR("Target defination file does not exist.")
    return()
endif()

# call generate.lua to generate target.h and target.lua
execute_process(
    COMMAND lua generate.lua ${TARGET}
    WORKING_DIRECTORY ${PROJECT_TARGET_LIST_DIR}
    RESULT_VARIABLE GEN_RESULT
)

if(NOT EXISTS ${PROJECT_TARGET_DIR}/target.h OR NOT EXISTS ${PROJECT_TARGET_DIR}/target.cmake)
    LOG_ERROR("Run target/generate.lua with target ${PROJECT_TARGET} failed.")
    return()
endif()

include("${PROJECT_TARGET_DIR}/target.cmake")

if(NOT DEFINED TARGET_MCU OR NOT DEFINED TARGET_MCU_SERIES OR NOT DEFINED TARGET_BUILD_TOOLCHAIN)
    LOG_ERROR("Missing defination(s) in ${PROJECT_TARGET_DIR}/target.cmake.")
    return()
else()
    LOG_INFO("Target mcu \"${TARGET_MCU}\" belong to series \"${TARGET_MCU_SERIES}\", using toolchain \"${TARGET_BUILD_TOOLCHAIN}\".")
endif()

if(${TARGET_MCU_SERIES} STREQUAL "STM32H7")
    set(TAREGT_MCU_FLAGS "")
endif()

LOG_INFO("Add library ${LIB_TARGET_DEF_INTERFACE}")
add_library(${LIB_TARGET_DEF_INTERFACE} INTERFACE)
target_include_directories(${LIB_TARGET_DEF_INTERFACE}
    INTERFACE
    ${PROJECT_TARGET_DIR}
)
target_compile_definitions(${LIB_TARGET_DEF_INTERFACE}
    INTERFACE
    ${TARGET_DEFINES_SYMBOLS}
)