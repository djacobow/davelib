#include "dave/event.h"
#include "dave/log.h"

namespace dave::event {


EventID_t::EventID_t(uint32_t id) : id_(id) {};

EventID_t::EventID_t() : id_(0) {};

auto EventID_t::operator==(const EventID_t &other) const {
    return other.id_ == id_;
}

auto EventID_t::Less(const EventID_t &other) const {
    return id_ < other.id_;
}

std::string EventID_t::Show() const {
    return std::to_string(id_);
}

auto operator<(const EventID_t &a, const EventID_t &b) {
    return a.Less(b);
}

std::map<std::string, EventID_t> EventSystem_c::StringsToMap(std::vector<std::string> nlist) {
    std::map<std::string, EventID_t> tempmap;
    uint32_t index = 0;
    tempmap["evs_shutdown"] = EventID_t(index++);
    for (auto &name: nlist) {
        tempmap[name] = EventID_t(index++);
    }
    return tempmap;
};

std::map<EventID_t, std::string> EventSystem_c::MapToMap(const std::map<std::string, EventID_t> &in) {
    std::map<EventID_t, std::string> out;
    for (const auto &e : in) {
        out[e.second] = e.first;
    }
    return out;
}

EventSystem_c::~EventSystem_c() {
    Send("evs_shutdown");
}

EventSystem_c::EventSystem_c(const std::vector<std::string> namelist, const std::vector<Subscriber_t> &subs) :
    types_by_name_(EventSystem_c::StringsToMap(namelist)),
    types_by_id_(EventSystem_c::MapToMap(types_by_name_)),
    subscribers_(subs) {

    send_thread_ = std::async(
        std::launch::async,
        [this]() {
            const auto shutdown_ev = types_by_name_.find("evs_shutdown")->second;
            uint32_t count = 0;
            while (true) {
                auto ev = send_queue_.PopBlock();
                count++;

                for (auto &subscriber : subscribers_) {
                    subscriber(ev, types_by_id_.find(ev)->second);
                }
                if (ev == shutdown_ev) {
                    break;
                }
            }
            return count;
        }
    );
}
        
void EventSystem_c::Send(const EventID_t &ev) {
    send_queue_.Push(ev);
}

std::optional<EventID_t> EventSystem_c::EventByName(const std::string &name) {
    auto it = types_by_name_.find(name);
    if (it == types_by_name_.end()) {
        return std::nullopt;
    }
    return it->second;
}

bool EventSystem_c::Send(const std::string &name) {
    auto it = types_by_name_.find(name);
    if (it == types_by_name_.end()) {
        return false;
    }
    Send(it->second);
    return true;
}

void EventSystem_c::Subscribe(Subscriber_t s) {
    subscribers_.push_back(s);
}

bool EventSystem_c::EventValid(const std::string &name) {
    return types_by_name_.find(name) != types_by_name_.end();
}

bool EventSystem_c::EventValid(const EventID_t &id) {
    return types_by_id_.find(id) != types_by_id_.end();
}

} // namespace dave::event
