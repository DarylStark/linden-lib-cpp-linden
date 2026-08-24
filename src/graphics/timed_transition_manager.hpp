#pragma once

#include "../system/clock.hpp"
#include "transition.hpp"
#include <concepts>
#include <map>
#include <memory>

namespace graphics
{
    class TimedTransitionManager
    {
    private:
        linden::system::Clock &_clockSource;
        std::map<std::size_t, std::unique_ptr<Transition>> _transitions;
        std::size_t _idx{0};

    public:
        TimedTransitionManager(linden::system::Clock &clockSource);

        template <typename T, typename... Args>
            requires std::derived_from<T, Transition>
        std::size_t addTransition(Args &&...args)
        {
            std::size_t id = _idx++;
            _transitions.try_emplace(
                id, std::make_unique<T>(std::forward<Args>(args)...));
            return id;
        }

        void updateAll(bool autoRemove = true);
        void update(std::size_t index, bool autoRemove = true);
    };
} // namespace graphics