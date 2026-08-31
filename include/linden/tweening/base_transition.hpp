#pragma once

namespace linden::tweening
{
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
        bool isFirst;
        size_t transitionIndex{};
    };

    template <typename ValueT>
    class BaseTransition
    {
    public:
        virtual UpdateResult update(ValueT elapsedValue) = 0;
    };
} // namespace linden::tweening