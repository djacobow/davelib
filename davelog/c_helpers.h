#pragma once

#define C_HELPERS_INCLUDED
#ifdef CPP_HELPERS_INCLUDED
    #error "A given translation unit should include the c_helpers.h file or the cpp_helpers.h file, but not both"
#endif

#include <stddef.h>
#include "davelog/levels_names.h"

#ifdef __cplusplus
extern "C" {
#endif

#define C_LOG_FN_DECL(level) void DaveLog_##level(const char *filename, size_t line, const char *funcname, const char *fmt, ...);

// this declares a c function that wraps the c++, for each level names in the macro in levels_names.h
LOG_LEVELS(C_LOG_FN_DECL);

#ifdef __cplusplus
} // extern "C"
#endif

#define __LOG_LEVEL(l, m, ...) \
    do { \
        DaveLog_##l(__FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    } while (0)

#define LOG_IF(b, l, m, ...) \
    if (b) { \
        DaveLog_##l(__FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    }


#define L(l, m, ...) __LOG_LEVEL(l, m, ##__VA_ARGS__)

