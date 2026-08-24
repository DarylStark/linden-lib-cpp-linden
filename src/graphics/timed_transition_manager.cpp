#include "timed_transition_manager.hpp"

namespace graphics
{
    TimedTransitionManager::TimedTransitionManager(
        linden::system::Clock &clockSource)
        : _clockSource(clockSource)
    {
    }

    void TimedTransitionManager::updateAll(bool autoRemove)
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

    void TimedTransitionManager::update(std::size_t index, bool autoRemove)
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
} // namespace graphics