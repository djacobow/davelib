#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

// A simple and hopefully correct generic thread-safe queue class

namespace dave::async {

template<class T>
class TSafeQueue_c {
    public:
        TSafeQueue_c() = default;
        void Push(T e) {
            std::lock_guard<std::mutex> lock(mtx_);
            q_.push(e);
            cv_push_.notify_one();
        }

        bool Empty() {
            std::unique_lock<std::mutex> lock(mtx_);
            return q_.empty();
        }

        void WaitEmpty() {
            std::unique_lock<std::mutex> lock(mtx_);
            if (q_.empty()) {
                return;
            }
            cv_pop_.wait(lock, [this]{return q_.empty();});
        }

        // does not block on non-emptiness but will still block
        // to get the mutex
        bool PopNoBlock(T& e) {
            std::unique_lock<std::mutex> lock(mtx_);
            if (q_.empty()) {
                return false;
            }
            e = q_.front();
            q_.pop();
            cv_pop_.notify_all();
            return true;
        }

        // this blocks on the mutex *and* non-emptiness
        T PopBlock() {
            T elem;
            std::unique_lock<std::mutex> lock(mtx_);
            cv_push_.wait(lock, [this]{return !q_.empty();});
            if (!q_.empty()) {
                elem = q_.front();
                q_.pop();
                cv_pop_.notify_all();
            }
            return elem;
        }
    private:    
        std::mutex mtx_;
        std::condition_variable cv_push_;
        std::condition_variable cv_pop_;
        std::queue<T> q_;
};

}
