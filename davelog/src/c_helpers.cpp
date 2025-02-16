#include "davelog/logger.hpp"
#include "davelog/levels.h"

#ifdef __cplusplus
extern "C" {
#endif

#define C_LOG_FN_IMPL(l1, l2) \
    void DaveLog_##l1(const char *filename, size_t line, const char *funcname, const char *fmt, ...) { \
        va_list args; \
        va_start(args, fmt); \
        dave::log::Logger_c::Get().Log(l2, filename, line, funcname, fmt, args); \
        va_end(args); \
    }

C_LOG_FN_IMPL(very_verbose, dave::log::Level_e::very_verbose);
C_LOG_FN_IMPL(verbose, dave::log::Level_e::verbose);
C_LOG_FN_IMPL(debug, dave::log::Level_e::debug);
C_LOG_FN_IMPL(info, dave::log::Level_e::info);
C_LOG_FN_IMPL(notice, dave::log::Level_e::notice);
C_LOG_FN_IMPL(warning, dave::log::Level_e::warning);
C_LOG_FN_IMPL(error, dave::log::Level_e::error);
C_LOG_FN_IMPL(fatal, dave::log::Level_e::fatal);

#ifdef __cplusplus
} // extern "C"
#endif
