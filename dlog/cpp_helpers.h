
#pragma once
#define CPP_HELPERS_INCLUDED
#ifdef C_HELPERS_INCLUDED
    #error "A given translation unit should include the c_helpers.h file or the cpp_helpers.h file, but not both"
#endif

#include "dlog/logger.hpp"

// a shortcut to conjure up the logger object:
#define LOGGER dlog::Logger_c::Get()

// to force he logger to close open files:
#define LOG_DONE() LOGGER.Done()

#define __LOG_LEVEL(l, m, ...) \
    do { \
        dlog::Logger_c::Get().Log(dlog::Level_e::l, __FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    } while (0)

#define __LOG_IF(b, l, m, ...) \
    if (b) { \
        dlog::Logger_c::Get().Log(dlog::Level_e::l, __FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    }

// This is the *primary* way to call the logger using the printf syntax
#define L(level, m, ...) \
    __LOG_LEVEL(level, m, ##__VA_ARGS__)


#define L_IF(level, b, m, ...) \
    __LOG_IF(b, level, m, ##__VA_ARGS__)


#define __L_ENDL_LEVEL(l) \
    dlog::stream_end_c { \
        l, __FILE__, __LINE__, __func__ \
    }

// when using the stream syntax, you end the message with one of these
// to indicate what loglevel should receive the message
#define L_ENDL(l)        __L_ENDL_LEVEL(dlog::Level_e::l)

// clang-format on
