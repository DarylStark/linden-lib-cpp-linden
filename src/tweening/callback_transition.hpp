#pragma once

#include "transition.hpp"
#include <chrono>

namespace tweening
{
    using TransitionCallback = std::function<void(float)>;

    template <typename ValueT>
    class CallbackTransition : public Transition<ValueT>
    {
    private:
        TransitionCallback _callback;
        void _update(float normalizedProgress) override
        {
            if (!_callback)
                return;
            _callback(normalizedProgress);
        }

    public:
        CallbackTransition(
            EasingFunction easingFn, ValueT durationUs,
            TransitionCallback callback,
            std::chrono::microseconds delayUs = std::chrono::microseconds(0))
            : Transition<ValueT>(easingFn, durationUs, delayUs),
              _callback(callback)
        {
        }
    };
} // namespace tweening