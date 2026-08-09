#include "transition.hpp"

namespace graphics
{
    Transition::Transition(std::unique_ptr<TweeningStrategy> &&strategy,
                           TransitionCallback callback, uint64_t durationUs)
        : _tweeningStrategy(std::move(strategy)), _callback(callback),
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

        _callback(_tweeningStrategy->apply(normalized));

        if (normalized == 1.0)
        {
            reset();
        }
    }

    void Transition::reset()
    {
        _startTime = 0;
    }
} // namespace graphics