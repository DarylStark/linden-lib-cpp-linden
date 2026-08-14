#include "transition.hpp"

namespace graphics
{
    Transition::Transition(EasingFunction easingFn,
                           std::chrono::microseconds durationUs,
                           TransitionCallback callback)
        : _easingFn(std::move(easingFn)), _callback(std::move(callback)),
          _durationUs(durationUs)
    {
    }

    void Transition::_runCallback(float normalizedProgress)
    {
        if (!_callback)
            return;
        _callback(_easingFn(normalizedProgress));
    }

    float Transition::update(uint64_t elapsedUs)
    {
        if (_state == TransitionState::DONE)
        {
            return 1.0;
        }

        if (_state == TransitionState::PENDING)
        {
            _startTime = elapsedUs;
            _state = TransitionState::RUNNING;
        }

        // Get the normalized detla time
        uint64_t runtime = elapsedUs - _startTime;

        float normalized = static_cast<float>(runtime) /
                           static_cast<float>(_durationUs.count());

        normalized = std::clamp(normalized, 0.0f, 1.0f);

        _runCallback(normalized);

        if (normalized == 1.0)
        {
            _state = TransitionState::DONE;
        }

        return normalized;
    }

    void Transition::reset()
    {
        _startTime = 0;
        _state = TransitionState::PENDING;
    }

    bool Transition::isDone() const
    {
        return _state == TransitionState::DONE;
    }
} // namespace graphics