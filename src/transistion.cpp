#include "transition.hpp"

namespace graphics
{
    Transition::Transition(EasingFunction easingFn, uint64_t durationUs,
                           TransitionCallback callback)
        : _easingFn(std::move(easingFn)), _callback(std::move(callback)),
          _durationUs(durationUs)
    {
    }

    void Transition::tick(uint64_t elapsedUs)
    {
        if (_state == TransitionState::DONE)
        {
            return;
        }

        if (_state == TransitionState::PENDING)
        {
            _startTime = elapsedUs;
            _state = TransitionState::RUNNING;
        }

        // Get the normalized detla time
        float normalized = 0;
        uint64_t runtime = elapsedUs - _startTime;

        if (runtime > 0)
        {
            normalized =
                static_cast<float>(runtime) / static_cast<float>(_durationUs);
            // TODO: Clamp
        }

        normalized = std::clamp(normalized, 0.0f, 1.0f);

        if (_callback)
        {
            _callback(_easingFn(normalized));
        }

        if (runtime > _durationUs)
        {
            _state = TransitionState::DONE;
        }
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