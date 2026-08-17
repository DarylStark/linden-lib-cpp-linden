#pragma once

#include <chrono>
#include <cstdint>

namespace graphics
{
    class Clock
    {
    public:
        virtual std::chrono::microseconds getElapsedTime() const = 0;
        virtual std::chrono::microseconds restart() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual bool isRunning() const = 0;
    };

    class StlClock : public Clock
    {
    private:
        std::chrono::steady_clock::time_point _start;
        bool _isRunning;

    public:
        StlClock();
        std::chrono::microseconds getElapsedTime() const;
        std::chrono::microseconds restart();
        void start();
        void stop();
        bool isRunning() const;
    };

} // namespace graphics