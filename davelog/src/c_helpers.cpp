#include "davelog/logger.hpp"
#include "davelog/levels.h"

#ifdef __cplusplus
extern "C" {
#endif

#define C_LOG_FN_IMPL(l) \
    void DaveLog_##l(const char *filename, size_t line, const char *funcname, const char *fmt, ...) { \
        va_list args; \
        va_start(args, fmt); \
        dave::log::Logger_c::Get().Log(dave::log::Level_e::l, filename, line, funcname, fmt, args); \
        va_end(args); \
    };

// creates a "C" callable function for each log level using the names in level_names.h and the
// implementation macro above:
LOG_LEVELS(C_LOG_FN_IMPL);

#ifdef __cplusplus
} // extern "C"
#endif
