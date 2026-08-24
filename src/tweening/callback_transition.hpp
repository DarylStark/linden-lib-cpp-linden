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
        CallbackTransition(EasingFunction easingFn, ValueT duration,
                           TransitionCallback callback,
                           ValueT delay = ValueT(0))
            : Transition<ValueT>(easingFn, duration, delay), _callback(callback)
        {
        }
    };
} // namespace tweening