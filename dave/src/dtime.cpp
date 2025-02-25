#include "dave/dtime.h"

namespace dave::time {

auto operator==(const DTime &l, const DTime &r) -> bool {
    return l.Raw() == r.Raw();
}

} // namespace dave::time
