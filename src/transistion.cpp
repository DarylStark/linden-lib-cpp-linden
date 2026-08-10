#include "transition.hpp"

namespace graphics
{
    Transition::Transition(EasingFunction easingFn, uint64_t durationUs,
                           TransitionCallback callback) noexcept
        : _easingFn(std::move(easingFn)), _callback(callback),
          _durationUs(durationUs)
    {
    }

    void Transition::tick(uint64_t dt)
    {
        if (_startTime == 0)
        {
            _startTime = dt;
        }

        // Get the normalized detla time
        float normalized = 0;
        uint64_t runtime = dt - _startTime;

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
    }

    void Transition::reset()
    {
        _startTime = 0;
    }
} // namespace graphics