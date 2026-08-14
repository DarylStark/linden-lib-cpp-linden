#pragma once

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
        uint64_t _durationUs;
        uint64_t _startTime{};

        EasingFunction _easingFn;
        TransitionCallback _callback;

        TransitionState _state = TransitionState::PENDING;

        void _runCallback(uint64_t normalizedProgress);

    public:
        Transition(EasingFunction easingFn, uint64_t durationUs,
                   TransitionCallback callback = nullptr);

        // TODO: take in a more "C++"'y type. Something from `std::chrono`?
        virtual float update(uint64_t elapsedUs);

        void reset();

        bool isDone() const;
    };
} // namespace graphics