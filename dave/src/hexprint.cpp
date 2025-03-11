#include "dave/hexprint.h"

#include <cctype>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

namespace dave::hex {

std::string bin2hex(const void *p, size_t l) {
    const char *digits = "0123456789abcdef";
    const uint8_t *s = static_cast<const uint8_t *>(p);
    std::stringstream ss;
    std::string os;
    os.resize(l * 2, ' ');
    if (l) {
        for (size_t i = 0; i < l; i++) {
            const uint8_t b = s[i];
            os[2*i + 0] = digits[(b >> 4) & 0xf];
            os[2*i + 1] = digits[(b) & 0xf];
        }
    }
    return os;
}

std::string bin2hex(const std::string &s) {
    return bin2hex(s.data(), s.size());
}

std::string bin2printable(const void *p, size_t l) {
    const char *s = static_cast<const char *>(p);
    std::string os;
    os.resize(l);
    for (size_t i=0; i<l; i++) {
        os[i] = isprint(s[i]) ? s[i] : '.';
    }
    return os;
}

static uint32_t byteswap32(uint32_t in) {
    uint32_t out = in;
    out = ((out & 0x0000ffffULL) << 16) | ((out & 0xffff0000ULL) >> 16);
    out = ((out & 0x00ff00ffULL) << 8)  | ((out & 0xff00ff00ULL) >> 8);
    return out;
};

static uint64_t byteswap64(uint64_t in) {
    return (byteswap32(in >> 32)) | (static_cast<uint64_t>(byteswap32(in & 0xffffffff)) << 32);
}

std::string bin2hex_canonical(const std::string &s) {
    return bin2hex_canonical(s.data(), s.size());
}


std::string bin2hex_canonical(const void *p, size_t l) {
    std::stringstream ss;
    ss << "\n";
    const uint8_t *ip = static_cast<const uint8_t *>(p);
    for (size_t i = 0; i < l; i += 16) {
        const size_t ll = std::min(l - i, static_cast<size_t>(16));
#if defined(__SIZEOF_POINTER__) && (__SIZEOF_POINTER__ == 4)
        const size_t irev = byteswap32(i);
#else
        const size_t irev = byteswap64(i);
#endif
        ss << std::setw(0) << "0x" << bin2hex(&irev, sizeof(irev));
        ss << " | " << std::left << std::setfill(' ') << std::setw(16)
           << bin2printable(ip, ll);
        ss << " | " << bin2hex(ip, ll) << "\n";
        ip += ll;
    };
    return ss.str();
};

}
