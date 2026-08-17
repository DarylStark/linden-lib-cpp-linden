#include "callback_transition.hpp"

namespace graphics
{
    void CallbackTransition::_update(float normalizedProgress)
    {
        if (!_callback)
            return;
        _callback(normalizedProgress);
    }

    CallbackTransition::CallbackTransition(EasingFunction easingFn,
                                           std::chrono::microseconds durationUs,
                                           TransitionCallback callback,
                                           std::chrono::microseconds delayUs)
        : Transition(easingFn, durationUs, delayUs), _callback(callback)
    {
    }
} // namespace graphics