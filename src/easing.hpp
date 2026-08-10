#pragma once

#include <cmath>
#include <cstdint>
#include <memory>

namespace math
{
    namespace easing
    {
        // Generic
        constexpr float linear(float normalizedTime) noexcept
        {
            return normalizedTime;
        }

        // Power easing In and Out
        constexpr float inOutQuad(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 2.0f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f) / 2.0f;
        }

        constexpr float inOutCubic(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 4.0f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f) / 2.0f;
        }

        constexpr float inOutQuart(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 8.0f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f) / 2.0f;
        }

        constexpr float inOutQuint(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 16.0f * f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f * f) / 2.0f;
        }

        constexpr float inOutSextic(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 32.0f * f * f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f * f * f) / 2.0f;
        }

        constexpr float inOutSeptic(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 64.0f * f * f * f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f * f * f * f) / 2.0f;
        }

        constexpr float inOutOctic(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 128.0f * f * f * f * f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f * f * f * f * f) / 2.0f;
        }

        constexpr float inOutNonic(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 256.0f * f * f * f * f * f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f * f * f * f * f * f) / 2.0f;
        }

        constexpr float inOutDecic(float normalizedTime) noexcept
        {
            if (normalizedTime < 0.5f)
            {
                float f = normalizedTime;
                return 512.0f * f * f * f * f * f * f * f * f * f * f;
            }
            float f = -2.0f * normalizedTime + 2.0f;
            return 1.0f - (f * f * f * f * f * f * f * f * f * f) / 2.0f;
        }

        // Smoothstep
        constexpr float inOutSmoothStep(float normalizedTime) noexcept
        {
            return normalizedTime * normalizedTime *
                   (3.f - 2.f * normalizedTime);
        }

        constexpr float inOutSmootherStep(float normalizedTime) noexcept
        {
            return normalizedTime * normalizedTime * normalizedTime *
                   (normalizedTime * (normalizedTime * 6 - 15) + 10);
        }

        // Trigonometric
        constexpr float inOutSine(float normalizedTime) noexcept
        {
            return (1.f -
                    std::cos(std::numbers::pi_v<float> * normalizedTime)) /
                   2.f;
        }

        // Exponental
        constexpr float inOutExpo(float normalizedTime) noexcept
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

        // Circular
        constexpr float inOutCirc(float normalizedTime) noexcept
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

        // Back
        constexpr float inOutBack(float normalizedTime) noexcept
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

        // Physical
        constexpr float inOutElastic(float normalizedTime) noexcept
        {
            float c5 = (2.0f * std::numbers::pi_v<float>) / 4.5f;

            if (normalizedTime < 0.5f)
            {
                float exp = std::pow(2.0f, 20.0f * normalizedTime - 10.0f);
                float sin = std::sin((20.0f * normalizedTime - 11.125f) * c5);
                return -(exp * sin) / 2.0f;
            }
            float exp = std::pow(2.0f, -20.0f * normalizedTime + 10.0f);
            float sin = std::sin((20.0f * normalizedTime - 11.125f) * c5);
            return (exp * sin) / 2.0f + 1.0f;
        }

        constexpr float _easeOutBounce(float normalizedTime) noexcept
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

        constexpr float inOutBounce(float normalizedTime) noexcept
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

        class inOutPoly
        {
        private:
            float _degree;

        public:
            inOutPoly(float degree) noexcept : _degree(degree) {};
            constexpr float operator()(float normalizedTime) noexcept
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
        };
    } // namespace easing
} // namespace math