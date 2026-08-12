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

    public:
        Transition(EasingFunction easingFn, uint64_t durationUs,
                   TransitionCallback callback);

        // TODO: rename to `update`
        // TODO: take in a more "C++"'y type. Something from `std::chrono`?
        // TODO: make this method return the value for the transition
        // TODO: make the callback optional
        void tick(uint64_t elapsedUs);

        void reset();

        bool isDone() const;
    };
} // namespace graphics