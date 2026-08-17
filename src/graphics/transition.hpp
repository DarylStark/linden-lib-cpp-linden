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
        std::chrono::microseconds _delayUs{};
        std::chrono::microseconds _startTime{};

        EasingFunction _easingFn;
        TransitionCallback _callback;

        TransitionState _state = TransitionState::PENDING;

        void _runCallback(float normalizedProgress);

    public:
        Transition(
            EasingFunction easingFn, std::chrono::microseconds durationUs,
            TransitionCallback callback = nullptr,
            std::chrono::microseconds delayUs = std::chrono::microseconds(0));

        float update(std::chrono::microseconds elapsedUs);

        void reset();

        bool isDone() const;
    };
} // namespace graphics