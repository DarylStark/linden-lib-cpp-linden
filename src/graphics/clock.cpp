#include "clock.hpp"

namespace graphics
{
    StlClock::StlClock()
    {
        start();
    }

    std::chrono::microseconds StlClock::getElapsedTime() const
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(steady_clock::now() - _start);
    }

    std::chrono::microseconds StlClock::restart()
    {
        using namespace std::chrono;
        auto elapsed = getElapsedTime();
        start();
        return elapsed;
    }

    void StlClock::start()
    {
        using namespace std::chrono;

        _start = steady_clock::now();
        _isRunning = true;
    }

    void StlClock::stop()
    {
        _isRunning = false;
    }

    bool StlClock::isRunning() const
    {
        return _isRunning;
    }
} // namespace graphics