#pragma once

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

        // TODO: rename to `update`
        // TODO: take in a more "C++"'y type. Something from `std::chrono`?
        // TODO: make this method return the value for the transition
        // TODO: make the callback optional
        // TODO: add a state (pending, running, done) so we can filter
        void tick(uint64_t dt);

        void reset();
    };
} // namespace graphics