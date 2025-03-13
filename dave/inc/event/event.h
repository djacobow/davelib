#pragma once

#include <future>
#include <map>
#include <string>
#include <vector>
#include <optional>
#include "dave/inc/async/tsafeq.h"

// Provides a simple event subsystem.
// * The event system is created with a named list of possible events.
// * A list of subscribers can also be added.
// * can be run in its own thread or not
// * If threaded:
//   * Events "added" are pushed into a queue
//   * A separate thread "drains" events and round-robins them to all the subscribers
// * otherwise, events are dispatched immediately in the caller's thread

namespace dave::event {

class EventID_t {
    public:
        EventID_t(uint32_t id);
        EventID_t();
        auto operator==(const EventID_t &other) const;
        auto Less(const EventID_t &other) const;
        std::string Show() const;
        
    private:
        uint32_t id_;
};

auto operator<(const EventID_t &a, const EventID_t &b);

using Subscriber_t = std::function<void(const EventID_t &, const std::string &)>;

class EventSystem_c {
    public:
        ~EventSystem_c();
        EventSystem_c(const std::vector<std::string> namelist, const std::vector<Subscriber_t> &subs = {}, bool own_thread = false);
        EventSystem_c() = delete;
        EventSystem_c(const EventSystem_c &other) = delete;

        void Send(const EventID_t &ev);
        bool Send(const std::string &name);

        // NB: subscribers will receive events from the event object's thread. If they
        // want to use the event, they should copy it in a thread safe manner
        void Subscribe(Subscriber_t s);

        std::optional<EventID_t> EventByName(const std::string &name);
        bool EventValid(const std::string &name);
        bool EventValid(const EventID_t &id);

    private:
        const std::map<std::string, EventID_t> types_by_name_;
        const std::map<EventID_t, std::string> types_by_id_;
        dave::async::TSafeQueue_c<EventID_t> send_queue_;
        std::future<uint32_t> send_thread_;
        std::vector<Subscriber_t> subscribers_;
        const bool own_thread_;

        void DispatchOne(const EventID_t &ev);
        static std::map<std::string, EventID_t> StringsToMap(std::vector<std::string> nlist);
        static std::map<EventID_t, std::string> MapToMap(const std::map<std::string, EventID_t> &in);
};

} // namespace dave::event
