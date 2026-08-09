#pragma once

#include "tweening_strategy.hpp"
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

        TweeningStrategy::UniquePtr _tweeningStrategy;
        TransitionCallback _callback;

    public:
        Transition(TweeningStrategy::UniquePtr &&strategy,
                   TransitionCallback callback, uint64_t durationUs);

        void tick(uint64_t dt);

        void reset();
    };
} // namespace graphics