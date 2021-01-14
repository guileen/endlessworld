// https://gist.github.com/darkf/8882611
#pragma once

#include <map>
#include <functional>
#include <typeinfo>
// Has the limitation that on<T> will not catch subtypes of T, only T.
// That may or may not be a problem for your usecase.
//
// It also doesn't (yet) let you use the subtype as an argument.
struct Event{};

typedef std::multimap<const std::type_info*,
					  const std::function<void(const Event&)>> EventMap;

namespace EventBus {
    namespace {
        // anonymouse namespace as private
        EventMap eventMap;
    }

    // template<typename EventWanted>
    // void on(const std::function<void(const EventWanted&)>& fn) {
    //     event::eventMap.emplace(&typeid(EventWanted), fn);
    // }
    template<typename EventWanted>
    void on(const std::function<void(const Event&)>& fn) {
        printf("register event listener %d\n", typeid(EventWanted).name());
        eventMap.emplace(&typeid(EventWanted), fn);
    }

    // template<typename EventWanted, typename Func>
    // void on(Func fn) {
    //     eventMap.emplace(&typeid(EventWanted), fn);
    // }

    void emit(const Event& event) {
        printf("Emit event: %s\n", typeid(event).name());
        auto range = eventMap.equal_range(&typeid(event));
        for(auto it = range.first; it != range.second; ++it)
            it->second(event);
    }
};
