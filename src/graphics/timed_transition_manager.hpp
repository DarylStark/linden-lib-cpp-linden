#pragma once

#include "../meta/concepts.hpp"
#include "../system/clock.hpp"
#include "transition.hpp"
#include <concepts>
#include <map>
#include <memory>

namespace graphics
{
    template <linden::meta::DurationLike DurationType>
    class TimedTransitionManager
    {
    private:
        linden::system::Clock<DurationType> &_clockSource;
        std::map<std::size_t,
                 std::unique_ptr<tweening::Transition<DurationType>>>
            _transitions;
        std::size_t _idx{0};

    public:
        TimedTransitionManager(linden::system::Clock<DurationType> &clockSource)
            : _clockSource(clockSource)
        {
        }

        template <typename T, typename... Args>
            requires std::derived_from<T, tweening::Transition<DurationType>>
        std::size_t addTransition(Args &&...args)
        {
            std::size_t id = _idx++;
            _transitions.try_emplace(
                id, std::make_unique<T>(std::forward<Args>(args)...));
            return id;
        }

        void updateAll(bool autoRemove = true)
        {
            auto dt = _clockSource.getElapsedTime();

            auto it = _transitions.begin();
            while (it != _transitions.end())
            {
                auto res = it->second->update(dt);
                if (autoRemove && res.state == tweening::TransitionState::Done)
                {
                    it = _transitions.erase(it);
                    continue;
                }
                ++it;
            }
        }

        void update(std::size_t index, bool autoRemove)
        {
            auto dt = _clockSource.getElapsedTime();

            auto it = _transitions.find(index);
            if (it != _transitions.end())
            {
                auto res = it->second->update(dt);
                if (autoRemove && res.state == tweening::TransitionState::Done)
                {
                    it = _transitions.erase(it);
                }
            }
        }
    };

    using TimedTransitionManagerNs =
        TimedTransitionManager<std::chrono::nanoseconds>;
    using TimedTransitionManagerUs =
        TimedTransitionManager<std::chrono::microseconds>;
    using TimedTransitionManagerMs =
        TimedTransitionManager<std::chrono::milliseconds>;
} // namespace graphics