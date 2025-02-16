
#pragma once
#define CPP_HELPERS_INCLUDED
#ifdef C_HELPERS_INCLUDED
    #error "A given translation unit should include the c_helpers.h file or the cpp_helpers.h file, but not both"
#endif

#include "davelog/logger.hpp"

#define LOG_DONE() dave::log::Logger_c::Get().Done()

#define LOG_LEVEL(l, m, ...) \
    do { \
        dave::log::Logger_c::Get() \
            .Log(l, __FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    } while (0)

#define LOG_IF(b, l, m, ...) \
    if (b) { \
        dave::log::Logger_c::Get() \
            .Log(l, __FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    }

// clang-format off
#define L_VVERBOSE(m, ...) LOG_LEVEL(dave::log::Level_e::very_verbose, m, ##__VA_ARGS__)
#define L_VERBOSE(m, ...)  LOG_LEVEL(dave::log::Level_e::verbose,      m, ##__VA_ARGS__)
#define L_DEBUG(m, ...)    LOG_LEVEL(dave::log::Level_e::debug,        m, ##__VA_ARGS__)
#define L_INFO(m, ...)     LOG_LEVEL(dave::log::Level_e::info,         m, ##__VA_ARGS__)
#define L_NOTICE(m, ...)   LOG_LEVEL(dave::log::Level_e::notice,       m, ##__VA_ARGS__)
#define L_WARNING(m, ...)  LOG_LEVEL(dave::log::Level_e::warning,      m, ##__VA_ARGS__)
#define L_ERROR(m, ...)    LOG_LEVEL(dave::log::Level_e::error,        m, ##__VA_ARGS__)
#define L_FATAL(m, ...)    LOG_LEVEL(dave::log::Level_e::fatal,        m, ##__VA_ARGS__)

#define L_WARN_IF(b, ...)  LOG_LEVEL_IF(b, dave::log::Level_e::warning, m, ##__VA_ARGS__)
#define L_ERROR_IF(b, ...) LOG_LEVEL_IF(b, dave::log::Level_e::error,   m, ##__VA_ARGS__)
#define L_FATAL_IF(b, ...) LOG_LEVEL_IF(b, dave::log::Level_e::fatal,   m, ##__VA_ARGS__)

#define L_ENDL_LEVEL(l) \
    dave::log::stream_end_c { \
        l, __FILE__, __LINE__, __func__ \
    }

#define L_ENDL_VVERBOSE  L_ENDL_LEVEL(dave::log::Level_e::very_verbose)
#define L_ENDL_VERBOSE   L_ENDL_LEVEL(dave::log::Level_e::verbose)
#define L_ENDL_DEBUG     L_ENDL_LEVEL(dave::log::Level_e::debug)
#define L_ENDL_INFO      L_ENDL_LEVEL(dave::log::Level_e::info)
#define L_ENDL_NOTICE    L_ENDL_LEVEL(dave::log::Level_e::notice)
#define L_ENDL_WARNING   L_ENDL_LEVEL(dave::log::Level_e::warning)
#define L_ENDL_ERROR     L_ENDL_LEVEL(dave::log::Level_e::error)
#define L_ENDL_FATAL     L_ENDL_LEVEL(dave::log::Level_e::fatal)
// clang-format on
