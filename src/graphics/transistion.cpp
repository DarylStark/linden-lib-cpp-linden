#include "transition.hpp"
#include <iostream>
#include <utility>

namespace graphics
{
    Transition::Transition(EasingFunction easingFn,
                           std::chrono::microseconds durationUs,
                           std::chrono::microseconds delayUs)
        : _easingFn(std::move(easingFn)), _durationUs(durationUs),
          _delayUs(delayUs)
    {
    }

    void Transition::_update(float normalizedProgress)
    {
        // Default `_update` doesn't do anything
    }

    float Transition::_getNormalizedProgress(
        std::chrono::microseconds elapsedUs) const
    {
        if (_state == TransitionState::DONE)
        {
            return 1.0;
        }

        if (_state != TransitionState::RUNNING)
        {
            return 0.0f;
        }

        auto elapsedSinceStart = elapsedUs - _startTime;

        if (elapsedSinceStart < _delayUs)
        {
            return 0.0f;
        }

        auto activeTime = elapsedSinceStart - _delayUs;
        float normalized = static_cast<float>(activeTime.count()) /
                           static_cast<float>(_durationUs.count());
        normalized = std::clamp(normalized, 0.0f, 1.0f);
        return normalized;
    }

    UpdateResult Transition::update(std::chrono::microseconds elapsedUs)
    {
        if (_state == TransitionState::PENDING)
        {
            _startTime = elapsedUs;
            _state = TransitionState::RUNNING;
        }

        float normalizedProgress = _getNormalizedProgress(elapsedUs);
        float easedProgress = _easingFn(normalizedProgress);
        _update(easedProgress);

        if (normalizedProgress >= 1.0)
        {
            _state = TransitionState::DONE;
        }

        return {normalizedProgress, easedProgress, _state};
    }

    void Transition::reset()
    {
        using namespace std::chrono_literals;
        _startTime = 0us;
        _state = TransitionState::PENDING;
    }

    bool Transition::isDone() const
    {
        return _state == TransitionState::DONE;
    }
} // namespace graphics