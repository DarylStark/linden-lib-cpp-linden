#pragma once

#include "../tweening/callback_transition.hpp"
#include "../tweening/transition.hpp"
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace linden::graphics
{
    using DefaultTimeUnit = std::chrono::microseconds;

    using TransitionNs = linden::tweening::Transition<std::chrono::nanoseconds>;
    using TransitionUs =
        linden::tweening::Transition<std::chrono::microseconds>;
    using TransitionMs =
        linden::tweening::Transition<std::chrono::milliseconds>;

    using CallbackTransitionNs =
        linden::tweening::CallbackTransition<std::chrono::nanoseconds>;
    using CallbackTransitionUs =
        linden::tweening::CallbackTransition<std::chrono::microseconds>;
    using CallbackTransitionMs =
        linden::tweening::CallbackTransition<std::chrono::milliseconds>;

    using Transition = TransitionUs;
    using CallbackTransition =
        linden::tweening::CallbackTransition<DefaultTimeUnit>;
} // namespace linden::graphics