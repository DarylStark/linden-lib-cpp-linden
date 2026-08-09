#include "tweening_strategy.hpp"
#include <cmath>
#include <iostream>

namespace graphics
{
    float Linear::apply(float normalizedTime)
    {
        return normalizedTime;
    }

    float EaseInOutQuad::apply(float normalizedTime)
    {
        return normalizedTime < 0.5 ? 2.f * normalizedTime * normalizedTime
                                    : 1.f - 2.f * (1.f - normalizedTime) *
                                                (1.f - normalizedTime);
    }

    float EaseInOutSmoothStep::apply(float normalizedTime)
    {
        return normalizedTime * normalizedTime * (3.f - 2.f * normalizedTime);
    }

    float EaseInOutSmootherStep::apply(float normalizedTime)
    {
        return normalizedTime * normalizedTime * normalizedTime *
               (normalizedTime * (normalizedTime * 6 - 15) + 10);
    }

    float EaseInOutSine::apply(float normalizedTime)
    {
        return (1.f - std::cos(std::numbers::pi_v<float> * normalizedTime)) /
               2.f;
    }
} // namespace graphics