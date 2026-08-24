#pragma once

#include "../meta/concepts.hpp"
#include <chrono>
#include <cstdint>

namespace linden::system
{
    template <linden::meta::DurationLike DurationType>
    class Clock
    {
    public:
        virtual DurationType getElapsedTime() const = 0;
        virtual DurationType restart() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual bool isRunning() const = 0;
    };

    template <linden::meta::DurationLike DurationType>
    class StlClock : public Clock<DurationType>
    {
    private:
        std::chrono::steady_clock::time_point _start;
        bool _isRunning;

    public:
        StlClock()
        {
            start();
        }

        DurationType getElapsedTime() const
        {
            using namespace std::chrono;
            return duration_cast<DurationType>(steady_clock::now() - _start);
        }

        DurationType restart()
        {
            using namespace std::chrono;
            auto elapsed = getElapsedTime();
            start();
            return elapsed;
        }

        void start()
        {
            using namespace std::chrono;

            _start = steady_clock::now();
            _isRunning = true;
        }

        void stop()
        {
            _isRunning = false;
        }

        bool isRunning() const
        {
            return _isRunning;
        }
    };

    using StlClockNs = StlClock<std::chrono::nanoseconds>;
    using StlClockUs = StlClock<std::chrono::microseconds>;
    using StlClockMs = StlClock<std::chrono::milliseconds>;
} // namespace linden::system