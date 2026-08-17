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
        PENDING,
        RUNNING,
        DONE
    };

    struct UpdateResult
    {
        float normalizedProgress;
        float easedProgress;
        TransitionState state;
    };

    class Transition
    {
    private:
        std::chrono::microseconds _durationUs;
        std::chrono::microseconds _delayUs{};
        std::chrono::microseconds _startTime{};

        EasingFunction _easingFn;

        TransitionState _state = TransitionState::PENDING;

        float _getNormalizedProgress(std::chrono::microseconds elapsedUs) const;

    protected:
        virtual void _update(float normalizedProgress);

    public:
        Transition(
            EasingFunction easingFn, std::chrono::microseconds durationUs,
            std::chrono::microseconds delayUs = std::chrono::microseconds(0));

        UpdateResult update(std::chrono::microseconds elapsedUs);

        void reset();

        bool isDone() const;
    };
} // namespace graphics