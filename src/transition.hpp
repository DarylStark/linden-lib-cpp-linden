#pragma once

#include "easing.hpp"
#include <cstdint>
#include <functional>
#include <memory>

namespace graphics
{
    using TransitionCallback = std::function<void(float)>;

    class Transition
    {
    private:
        uint64_t _durationUs;
        uint64_t _startTime{};

        math::easing::EasingStrategy::UniquePtr _tweeningStrategy;
        TransitionCallback _callback;

    public:
        Transition(math::easing::EasingStrategy::UniquePtr &&strategy,
                   uint64_t durationUs, TransitionCallback callback) noexcept;

        void tick(uint64_t dt);

        void reset();
    };
} // namespace graphics