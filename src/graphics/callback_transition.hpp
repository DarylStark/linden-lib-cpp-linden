#pragma once

#include "transition.hpp"

namespace graphics
{
    using TransitionCallback = std::function<void(float)>;

    class CallbackTransition : public Transition
    {
    private:
        TransitionCallback _callback;
        void _update(float normalizedProgress) override;

    public:
        CallbackTransition(
            EasingFunction easingFn, std::chrono::microseconds durationUs,
            TransitionCallback callback,
            std::chrono::microseconds delayUs = std::chrono::microseconds(0));
    };
} // namespace graphics