#pragma once

#include "easing.hpp"
#include <cstdint>
#include <functional>
#include <memory>

namespace graphics
{
    using EasingFunction = std::function<float(float)>;
    using TransitionCallback = std::function<void(float)>;

    class Transition
    {
    private:
        uint64_t _durationUs;
        uint64_t _startTime{};

        EasingFunction _easingFn;
        TransitionCallback _callback;

    public:
        Transition(EasingFunction easingFn, uint64_t durationUs,
                   TransitionCallback callback) noexcept;

        void tick(uint64_t dt);

        void reset();
    };
} // namespace graphics