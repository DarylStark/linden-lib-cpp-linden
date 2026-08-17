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

    float Transition::_calculateLinearProgress(
        std::chrono::microseconds elapsedUs) const
    {
        if (_state == TransitionState::Done)
        {
            return 1.0f;
        }

        if (_state != TransitionState::Running &&
            _state != TransitionState::Paused)
        {
            return 0.0f;
        }

        auto currentOrPauseTime =
            (_state == TransitionState::Paused) ? _pauseStartTime : elapsedUs;

        auto activeTime = (currentOrPauseTime - _startTime) - _delayUs;
        float normalized = static_cast<float>(activeTime.count()) /
                           static_cast<float>(_durationUs.count());

        return std::clamp(normalized, 0.0f, 1.0f);
    }

    UpdateResult Transition::update(std::chrono::microseconds elapsedUs)
    {
        bool isFirstRunningFrame = false;

        if (_state == TransitionState::Paused)
        {
            float normalizedProgress = _calculateLinearProgress(elapsedUs);
            float easedProgress = _easingFn(normalizedProgress);

            _update(easedProgress);

            return {normalizedProgress, easedProgress, _state, false};
        }

        if (_state == TransitionState::Pending)
        {
            _startTime = elapsedUs;

            if (_delayUs > std::chrono::microseconds::zero())
            {
                _state = TransitionState::Delayed;
            }
            else
            {
                _state = TransitionState::Running;
                isFirstRunningFrame = true;
            }
        }

        if (_state == TransitionState::Delayed)
        {
            if ((elapsedUs - _startTime) >= _delayUs)
            {
                _state = TransitionState::Running;
                isFirstRunningFrame = true;
            }
        }

        float normalizedProgress = _calculateLinearProgress(elapsedUs);
        float easedProgress = _easingFn(normalizedProgress);

        _update(easedProgress);

        if (_state == TransitionState::Running && normalizedProgress >= 1.0f)
        {
            _state = TransitionState::Done;
        }

        return {normalizedProgress, easedProgress, _state, isFirstRunningFrame};
    }

    void Transition::pause(std::chrono::microseconds elapsedUs)
    {
        if (_state == TransitionState::Delayed ||
            _state == TransitionState::Running)
        {
            _stateBeforePause = _state;
            _state = TransitionState::Paused;
            _pauseStartTime = elapsedUs;
        }
    }

    void Transition::resume(std::chrono::microseconds elapsedUs)
    {
        if (_state == TransitionState::Paused)
        {
            auto pausedDuration = elapsedUs - _pauseStartTime;
            _startTime += pausedDuration;
            _state = _stateBeforePause;
        }
    }

    void Transition::reset()
    {
        using namespace std::chrono_literals;
        _startTime = 0us;
        _state = TransitionState::Pending;
    }

    bool Transition::isDone() const
    {
        return _state == TransitionState::Done;
    }
} // namespace graphics