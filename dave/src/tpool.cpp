#include "dave/tpool.h"

namespace dave::async {

ThreadPool_c::ThreadPool_c(uint32_t tcount) :
    tcount_(tcount),
    running_(false),
    allow_add_(false),
    stopped_(true) {

    threads_.resize(tcount);
}

bool ThreadPool_c::Start() {
    if (!stopped_) {
        return false;
    }
    if (running_) {
        return false;
    }
    stopped_ = false;
    running_ = true;
    allow_add_ = true;
    for (uint32_t  i=0; i<tcount_; i++) {
        threads_[i] = std::async(
            std::launch::async, [this] {
                uint32_t count = 0;
                while (running_) {
                    queue_.PopBlock()();
                    count++;
                }
                return count;
            }
        );
    }
    return true;
} 

bool ThreadPool_c::Running() const {
    return !stopped_;
}


bool ThreadPool_c::Stop(bool wait_empty) {
    if (stopped_) {
        return true;
    }
    if (!running_) {
        return false;;
    }

    if (wait_empty) {
        allow_add_ = false;
        queue_.WaitEmpty();
    }
    running_ = false;
    for (uint32_t i=0; i<tcount_; i++) {
        queue_.Push([]() {});
    }
    for (uint32_t i=0;i<tcount_; i++) {
        threads_[i].wait();
    }
    stopped_ = true;
    return true;
}

bool ThreadPool_c::Add(Fn_c f) {
    if (!allow_add_) {
        return false;
    }
    queue_.Push(f);
    return true;
}

} // namespace dave::async
