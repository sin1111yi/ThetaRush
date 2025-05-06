set(LOG_LEVEL "INFO" CACHE STRING "Log output level (ERROR/WARN/INFO/DEBUG)")
set_property(CACHE LOG_LEVEL PROPERTY STRINGS ERROR WARN INFO DEBUG)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(LOG_COLOR_RESET "${Esc}[0m" CACHE INTERNAL "")
    set(LOG_COLOR_ERROR "${Esc}[1;31m" CACHE INTERNAL "LOG_COLOR_ERROR") # Bold Rad
    set(LOG_COLOR_WARN "${Esc}[1;33m" CACHE INTERNAL "LOG_COLOR_WARN") # Bold Yellow
    set(LOG_COLOR_INFO "${Esc}[1;32m" CACHE INTERNAL "LOG_COLOR_INFO") # Bold Green
    set(LOG_COLOR_DEBUG "${Esc}[1;36m" CACHE INTERNAL "LOG_COLOR_DEBUG") # Bold Blue
else()
    option(ENABLE_ANSI_COLORS "enable ANSI colors" OFF)
    if(ENABLE_ANSI_COLORS)
        set(LOG_COLOR_RESET " 001B[0m" CACHE INTERNAL "")
        set(LOG_COLOR_ERROR " 001B[1;31m" CACHE INTERNAL "LOG_COLOR_ERROR")
        set(LOG_COLOR_WARN " 001B[1;33m" CACHE INTERNAL "LOG_COLOR_WARN")
        set(LOG_COLOR_INFO " 001B[1;32m" CACHE INTERNAL "LOG_COLOR_INFO")
        set(LOG_COLOR_DEBUG " 001B[1;36m" CACHE INTERNAL "LOG_COLOR_DEBUG")
    else()
        set(LOG_COLOR_RESET "" CACHE INTERNAL "")
        set(LOG_COLOR_ERROR "" CACHE INTERNAL "LOG_COLOR_ERROR")
        set(LOG_COLOR_WARN "" CACHE INTERNAL "LOG_COLOR_WARN")
        set(LOG_COLOR_INFO "" CACHE INTERNAL "LOG_COLOR_INFO")
        set(LOG_COLOR_DEBUG "" CACHE INTERNAL "LOG_COLOR_DEBUG")
    endif()
endif()

function(__LOG_MESSAGE)
    set(oneValueArgs LEVEL PREFIX)
    set(multiValueArgs TEXT)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(LOG_COLOR "")

    # log level filter
    set(valid_levels ERROR WARN INFO DEBUG)

    # verify current log level
    list(FIND valid_levels "${ARG_LEVEL}" current_level_index)
    if(current_level_index EQUAL -1)
        message(WARNING "Invalied log level: ${ARG_LEVEL}")
        return()
    elseif(current_level_index EQUAL 0)
        set(LOG_COLOR ${LOG_COLOR_ERROR})
    elseif(current_level_index EQUAL 1)
        set(LOG_COLOR ${LOG_COLOR_WARN})
    elseif(current_level_index EQUAL 2)
        set(LOG_COLOR ${LOG_COLOR_INFO})
    elseif(current_level_index EQUAL 3)
        set(LOG_COLOR ${LOG_COLOR_DEBUG})
    endif()

    string(TOUPPER "${LOG_LEVEL}" normalized_log_level)
    list(FIND valid_levels "${normalized_log_level}" filter_level_index)
    if(filter_level_index EQUAL -1)
        message(WARNING "invalied LOG_LEVEL: ${LOG_LEVEL}, using default: INFO")
        set(filter_level_index 2)
    endif()

    if(current_level_index GREATER filter_level_index)
        return()
    endif()

    # message format
    string(CONFIGURE "${ARG_TEXT}" formatted_text @ONLY)

    if(current_level_index EQUAL 0)
        message(FATAL_ERROR "${LOG_COLOR} [${ARG_PREFIX}] ${formatted_text} ${LOG_COLOR_RESET}")
    else()
        message("${LOG_COLOR} [${ARG_PREFIX}] ${formatted_text} ${LOG_COLOR_RESET}")
    endif()
endfunction()

function(LOG_ERROR)
    __LOG_MESSAGE(LEVEL ERROR PREFIX "ERROR" TEXT ${ARGN})
endfunction()

function(LOG_WARN)
    __LOG_MESSAGE(LEVEL WARN PREFIX "WARN " TEXT ${ARGN})
endfunction()

function(LOG_INFO)
    __LOG_MESSAGE(LEVEL INFO PREFIX "INFO " TEXT ${ARGN})
endfunction()

function(LOG_DEBUG)
    __LOG_MESSAGE(LEVEL DEBUG PREFIX "DEBUG" TEXT ${ARGN})
endfunction()

