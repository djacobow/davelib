#include "dlog/dtime.h"

namespace dave::time {

bool operator==(const DTime &l, const DTime &r) {
    return l.Raw() == r.Raw();
}

}
