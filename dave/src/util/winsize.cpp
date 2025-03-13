#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdint>

#include "dave/inc/util/winsize.h"

namespace dave::util {

dave::err::ValueOr_c<TerminalDimensions_t> GetTerminalDimensions() {
#ifdef __linux__
    struct winsize ws = {};
    int fail = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    if (fail) {
        return E_(unavailable, "could not get terminal info");
    }
    return TerminalDimensions_t{.width = ws.ws_col, .height = ws.ws_row};
#else
    return E_(unavailable, "not supported on this platform");
#endif
}

} // namespace dave::util
