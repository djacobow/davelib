#include <string>
#include "dlog/init.h"
#include "dlog/logger.hpp"

namespace dlog {

void Init(const InitList_t &initlist) {
    for (const auto &iv : initlist) {
        Logger_c::Get().AddSubscriber(
            iv.name,
            std::make_unique<Subscriber_FilePtr_c>(
                iv.file_ptr,
                iv.level_mask,
                iv.style
            )
        );
    }
}

}  // namespace dlog

