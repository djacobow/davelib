#include <functional>
#include <future>
#include "dave/inc/async/tsafeq.h"

namespace dave::async {

class ThreadPool_c {
    public:
        using Fn_c = std::function<void()>;
        explicit ThreadPool_c(uint32_t tcount);
        bool Start();
        [[nodiscard]] bool Running() const;
        bool Stop(bool wait_empty = false);
        bool Add(Fn_c f);

    private:
        const uint32_t tcount_;
        std::atomic<bool> running_;
        bool allow_add_;
        bool stopped_;
        std::vector<std::future<uint32_t>> threads_;
        TSafeQueue_c<Fn_c> queue_;

};

} // namespace dave::async

