#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace graphics
{
    using EasingFunction = std::function<float(float)>;
    using TransitionCallback = std::function<void(float)>;

    enum class TransitionState
    {
        PENDING,
        RUNNING,
        DONE
    };

    class Transition
    {
    private:
        std::chrono::microseconds _durationUs;
        uint64_t _startTime{};

        EasingFunction _easingFn;
        TransitionCallback _callback;

        TransitionState _state = TransitionState::PENDING;

        void _runCallback(float normalizedProgress);

    public:
        Transition(EasingFunction easingFn,
                   std::chrono::microseconds durationUs,
                   TransitionCallback callback = nullptr);

        // TODO: take in a more "C++"'y type. Something from `std::chrono`?
        virtual float update(uint64_t elapsedUs);

        void reset();

        bool isDone() const;
    };
} // namespace graphics