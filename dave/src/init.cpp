#include <memory>
#include "dave/init.h"
#include "dave/logger.hpp"
#include "dave/subscriber.h"

namespace dave::log {

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

}  // namespace dave::log
