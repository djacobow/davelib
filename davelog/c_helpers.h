#pragma once

#define C_HELPERS_INCLUDED
#ifdef CPP_HELPERS_INCLUDED
    #error "A given translation unit should include the c_helpers.h file or the cpp_helpers.h file, but not both"
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define C_LOG_FN_DECL(level) void DaveLog_##level(const char *filename, size_t line, const char *funcname, const char *fmt, ...);

C_LOG_FN_DECL(very_verbose);
C_LOG_FN_DECL(verbose);
C_LOG_FN_DECL(debug);
C_LOG_FN_DECL(info);
C_LOG_FN_DECL(notice);
C_LOG_FN_DECL(warning);
C_LOG_FN_DECL(error);
C_LOG_FN_DECL(fatal);

#ifdef __cplusplus
} // extern "C"
#endif

#define LOG_LEVEL(l, m, ...) \
    do { \
        DaveLog_##l(__FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    } while (0)

#define LOG_IF(b, l, m, ...) \
    if (b) { \
        DaveLog_##l(__FILE__, __LINE__, __func__, m, ##__VA_ARGS__); \
    }

#define L_VVERBOSE(m, ...) LOG_LEVEL(very_verbose, m, ##__VA_ARGS__)
#define L_VERBOSE(m, ...)  LOG_LEVEL(verbose,      m, ##__VA_ARGS__)
#define L_INFO(m, ...)     LOG_LEVEL(info,         m, ##__VA_ARGS__)
#define L_NOTICE(m, ...)   LOG_LEVEL(notice,       m, ##__VA_ARGS__)
#define L_WARNING(m, ...)  LOG_LEVEL(warning,      m, ##__VA_ARGS__)
#define L_ERROR(m, ...)    LOG_LEVEL(error,        m, ##__VA_ARGS__)
#define L_FATAL(m, ...)    LOG_LEVEL(fatal,        m, ##__VA_ARGS__)
