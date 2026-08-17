#include "transition_manager.hpp"

namespace graphics
{
    TransitionManager::TransitionManager(Clock &clockSource)
        : _clockSource(clockSource)
    {
    }

    void TransitionManager::updateAll(bool autoRemove)
    {
        auto dt = _clockSource.getElapsedTime();

        auto it = _transitions.begin();
        while (it != _transitions.end())
        {
            auto res = it->second->update(dt);
            if (autoRemove && res.state == TransitionState::Done)
            {
                it = _transitions.erase(it);
                continue;
            }
            ++it;
        }
    }

    void TransitionManager::update(std::size_t index, bool autoRemove)
    {
        auto dt = _clockSource.getElapsedTime();

        auto it = _transitions.find(index);
        if (it != _transitions.end())
        {
            auto res = it->second->update(dt);
            if (autoRemove && res.state == TransitionState::Done)
            {
                it = _transitions.erase(it);
            }
        }
    }
} // namespace graphics