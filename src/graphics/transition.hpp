#pragma once

#include "../tweening/callback_transition.hpp"
#include "../tweening/transition.hpp"
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace graphics
{
    using DefaultTimeUnit = std::chrono::microseconds;

    using TransitionNs = tweening::Transition<std::chrono::nanoseconds>;
    using TransitionUs = tweening::Transition<std::chrono::microseconds>;
    using TransitionMs = tweening::Transition<std::chrono::milliseconds>;

    using CallbackTransitionNs =
        tweening::CallbackTransition<std::chrono::nanoseconds>;
    using CallbackTransitionUs =
        tweening::CallbackTransition<std::chrono::microseconds>;
    using CallbackTransitionMs =
        tweening::CallbackTransition<std::chrono::milliseconds>;

    using Transition = TransitionUs;
    using CallbackTransition = tweening::CallbackTransition<DefaultTimeUnit>;
} // namespace graphics