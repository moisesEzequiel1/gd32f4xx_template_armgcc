#pragma once
#include <array>
#include <functional>

namespace middleware {

class EventDispatcher {
public:
    using EventID = int;
    using EventCallback = std::function<void(int event_id, float value)>;

    static constexpr int MAX_EVENTS = 32;
    static constexpr int MAX_CALLBACKS = 8;

    void subscribe(EventID event_id, EventCallback cb);
    void dispatch(EventID event_id, float value = 0.0f) const;

private:
    std::array<std::array<EventCallback, MAX_CALLBACKS>, MAX_EVENTS> callbacks_;
    std::array<int, MAX_EVENTS> callback_counts_{0};
};

} // namespace middleware