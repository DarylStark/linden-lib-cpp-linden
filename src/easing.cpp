#include "easing.hpp"
#include <cmath>
#include <iostream>

namespace math
{
    namespace easing
    {
        float Linear::apply(float normalizedTime) noexcept
        {
            return normalizedTime;
        }

        float InOutQuad::apply(float normalizedTime) noexcept
        {
            return normalizedTime < 0.5 ? 2.f * normalizedTime * normalizedTime
                                        : 1.f - 2.f * (1.f - normalizedTime) *
                                                    (1.f - normalizedTime);
        }

        float InOutSmoothStep::apply(float normalizedTime) noexcept
        {
            return normalizedTime * normalizedTime *
                   (3.f - 2.f * normalizedTime);
        }

        float InOutSmootherStep::apply(float normalizedTime) noexcept
        {
            return normalizedTime * normalizedTime * normalizedTime *
                   (normalizedTime * (normalizedTime * 6 - 15) + 10);
        }

        float InOutSine::apply(float normalizedTime) noexcept
        {
            return (1.f -
                    std::cos(std::numbers::pi_v<float> * normalizedTime)) /
                   2.f;
        }

        float InOutBack::apply(float normalizedTime) noexcept
        {
            float c1 = 2.592389f;
            float c2 = c1 + 1.0f;

            if (normalizedTime < 0.5f)
            {
                float f = 2.0f * normalizedTime;
                return (f * f * (c2 * f - c1)) / 2.0f;
            }

            float f = 2.0f * normalizedTime - 2.0f;
            return (f * f * (c2 * f + c1) + 2.0f) / 2.0f;
        }

        float InOutCubic::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                return 4.0f * normalizedTime * normalizedTime * normalizedTime;
            }
            else
            {
                float f = -2.0f * normalizedTime + 2.0f;
                return 1.0f - (f * f * f) / 2.0f;
            }
        }

        float InOutElastic::apply(float normalizedTime) noexcept
        {
            float c5 = (2.0f * std::numbers::pi_v<float>) / 4.5f;

            if (normalizedTime < 0.5f)
            {
                float exp = std::pow(2.0f, 20.0f * normalizedTime - 10.0f);
                float sin = std::sin((20.0f * normalizedTime - 11.125f) * c5);
                return -(exp * sin) / 2.0f;
            }
            else
            {
                float exp = std::pow(2.0f, -20.0f * normalizedTime + 10.0f);
                float sin = std::sin((20.0f * normalizedTime - 11.125f) * c5);
                return (exp * sin) / 2.0f + 1.0f;
            }
        }

        float InOutBounce::_easeOutBounce(float normalizedTime) noexcept
        {
            float n1 = 7.5625f;
            float d1 = 2.75f;

            if (normalizedTime < 1.0f / d1)
            {
                return n1 * normalizedTime * normalizedTime;
            }
            else if (normalizedTime < 2.0f / d1)
            {
                normalizedTime -= 1.5f / d1;
                return n1 * normalizedTime * normalizedTime + 0.75f;
            }
            else if (normalizedTime < 2.625f / d1)
            {
                normalizedTime -= 2.25f / d1;
                return n1 * normalizedTime * normalizedTime + 0.9375f;
            }
            else
            {
                normalizedTime -= 2.625f / d1;
                return n1 * normalizedTime * normalizedTime + 0.984375f;
            }
        }

        float InOutBounce::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                return (1.0f - _easeOutBounce(1.0f - 2.0f * normalizedTime)) /
                       2.0f;
            }
            else
            {
                return (1.0f + _easeOutBounce(2.0f * normalizedTime - 1.0f)) /
                       2.0f;
            }
        }

        float InOutQuart::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 8.0f * f * f * f * f;
            }
            else
            {
                float f = -2.0f * normalizedTime + 2.0f;
                return 1.0f - (f * f * f * f) / 2.0f;
            }
        }

        float InOutQuint::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 16.0f * f * f * f * f;
            }
            else
            {
                float f = -2.0f * normalizedTime + 2.0f;
                return 1.0f - (f * f * f * f * f) / 2.0f;
            }
        }

        float InOutExpo::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                return std::exp2f(20.0f * normalizedTime - 10.0f) / 2.0f;
            }
            else
            {
                return (2.0f - std::exp2f(-20.0f * normalizedTime + 10.0f)) /
                       2.0f;
            }
        }

        float InOutCirc::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = 2.0f * normalizedTime;
                return (1.0f - std::sqrtf(1.0f - f * f)) / 2.0f;
            }
            else
            {
                float f = -2.0f * normalizedTime + 2.0f;
                return (std::sqrtf(1.0f - f * f) + 1.0f) / 2.0f;
            }
        }

        float InOutSextic::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 32.0f * f * f * f * f * f * f;
            }
            else
            {
                float f = -2.0f * normalizedTime + 2.0f;
                return 1.0f - (f * f * f * f * f * f) / 2.0f;
            }
        }

        InOutPoly::InOutPoly(float degree) noexcept : _degree(degree) {}

        float InOutPoly::apply(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                return std::exp2f(_degree - 1.0f) *
                       std::pow(normalizedTime, _degree);
            }
            else
            {
                float f = -2.0f * normalizedTime + 2.0f;
                return 1.0f - (std::pow(f, _degree) / 2.0f);
            }
        }
    } // namespace easing
} // namespace math