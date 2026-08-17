#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace graphics
{
    using EasingFunction = std::function<float(float)>;

    enum class TransitionState
    {
        Pending,
        Delayed,
        Running,
        Paused,
        Done
    };

    struct UpdateResult
    {
        float normalizedProgress;
        float easedProgress;
        TransitionState state;
        bool isFirstFrame;
    };

    class Transition
    {
    private:
        std::chrono::microseconds _durationUs;
        std::chrono::microseconds _delayUs{0};
        std::chrono::microseconds _startTime{0};

        // Pause members
        TransitionState _stateBeforePause{TransitionState::Pending};
        std::chrono::microseconds _pauseStartTime{0};

        EasingFunction _easingFn;

        TransitionState _state = TransitionState::Pending;

        float
        _calculateLinearProgress(std::chrono::microseconds elapsedUs) const;

    protected:
        virtual void _update(float normalizedProgress);

    public:
        Transition(
            EasingFunction easingFn, std::chrono::microseconds durationUs,
            std::chrono::microseconds delayUs = std::chrono::microseconds(0));

        UpdateResult update(std::chrono::microseconds elapsedUs);

        void pause(std::chrono::microseconds elapsedUs);
        void resume(std::chrono::microseconds elapsedUs);

        void reset();
        bool isDone() const;
    };
} // namespace graphics