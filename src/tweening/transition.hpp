#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace tweening
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
        bool isFirst;
    };

    template <typename T>
    concept DurationLike = requires(const T &t) {
        typename T::rep;
        typename T::period;
        { t.count() };
    };

    template <DurationLike T>
    float toFloat(const T &value)
    {
        return static_cast<float>(value.count());
    }

    template <typename T>
    float toFloat(const T &value)
    {
        return static_cast<float>(value);
    }

    template <typename ValueT>
    class Transition
    {
    private:
        ValueT _maxValue;
        ValueT _skipValue{};
        ValueT _startValue{};
        ValueT _pauseStartValue{};

        // Pause members
        TransitionState _stateBeforePause{TransitionState::Pending};

        EasingFunction _easingFn;

        TransitionState _state = TransitionState::Pending;

        float _calculateLinearProgress(ValueT elapsedValue) const
        {
            if (_state == TransitionState::Done)
            {
                return 1.0f;
            }

            if (_state != TransitionState::Running &&
                _state != TransitionState::Paused)
            {
                return 0.0f;
            }

            auto currentOrPauseValue = (_state == TransitionState::Paused)
                                           ? _pauseStartValue
                                           : elapsedValue;

            auto activeValue = (currentOrPauseValue - _startValue) - _skipValue;
            float normalized = static_cast<float>(toFloat(activeValue)) /
                               static_cast<float>(toFloat(_maxValue));

            return std::clamp(normalized, 0.0f, 1.0f);
        }

    protected:
        virtual void _update(float normalizedProgress)
        {
            // Default `_update` doesn't do anything
        }

    public:
        Transition(EasingFunction easingFn, ValueT maxValue,
                   ValueT skipValue = ValueT{})
            : _easingFn(std::move(easingFn)), _maxValue(maxValue),
              _skipValue(skipValue)
        {
        }

        UpdateResult update(ValueT elapsedValue)
        {
            bool isFirst = false;

            if (_state == TransitionState::Paused)
            {
                float normalizedProgress =
                    _calculateLinearProgress(elapsedValue);
                float easedProgress = _easingFn(normalizedProgress);

                _update(easedProgress);

                return {normalizedProgress, easedProgress, _state, false};
            }

            if (_state == TransitionState::Pending)
            {
                _startValue = elapsedValue;

                if (_skipValue > ValueT::zero())
                {
                    _state = TransitionState::Delayed;
                }
                else
                {
                    _state = TransitionState::Running;
                    isFirst = true;
                }
            }

            if (_state == TransitionState::Delayed)
            {
                if ((elapsedValue - _startValue) >= _skipValue)
                {
                    _state = TransitionState::Running;
                    isFirst = true;
                }
            }

            float normalizedProgress = _calculateLinearProgress(elapsedValue);
            float easedProgress = _easingFn(normalizedProgress);

            _update(easedProgress);

            if (_state == TransitionState::Running &&
                normalizedProgress >= 1.0f)
            {
                _state = TransitionState::Done;
            }

            return {normalizedProgress, easedProgress, _state, isFirst};
        }

        void pause(ValueT elapsedUs)
        {
            if (_state == TransitionState::Delayed ||
                _state == TransitionState::Running)
            {
                _stateBeforePause = _state;
                _state = TransitionState::Paused;
                _pauseStartValue = elapsedUs;
            }
        }

        void resume(ValueT elapsedUs)
        {
            if (_state == TransitionState::Paused)
            {
                auto pausedValue = elapsedUs - _pauseStartValue;
                _startValue += pausedValue;
                _state = _stateBeforePause;
            }
        }

        void reset()
        {
            using namespace std::chrono_literals;
            _startValue = ValueT{};
            _state = TransitionState::Pending;
        }

        bool isDone() const
        {
            return _state == TransitionState::Done;
        }
    };
} // namespace tweening