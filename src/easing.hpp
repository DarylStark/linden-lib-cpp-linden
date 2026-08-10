#pragma once

#include <cmath>
#include <cstdint>
#include <memory>

namespace math
{
    namespace easing
    {
        namespace helpers
        {
            template <typename InFunc>
            constexpr float makeEaseOut(InFunc &&inFunc, float t) noexcept
            {
                return 1.0f - inFunc(1.0f - t);
            }

            template <typename InFunc>
            constexpr float makeEaseInOut(InFunc &&inFunc, float t) noexcept
            {
                if (t < 0.5f)
                {
                    return inFunc(t * 2.0f) / 2.0f;
                }
                return (1.0f + makeEaseOut(inFunc, t * 2.0f - 1.0f)) / 2.0f;
            }
        } // namespace helpers

        // Generic
        constexpr float linear(float normalizedTime) noexcept
        {
            return normalizedTime;
        }

        // Power easing In and Out
        constexpr float inQuad(float t) noexcept
        {
            return t * t;
        }

        constexpr float outQuad(float t) noexcept
        {
            return helpers::makeEaseOut(inQuad, t);
        }

        constexpr float inOutQuad(float t) noexcept
        {
            return helpers::makeEaseInOut(inQuad, t);
        }

        constexpr float inCubic(float t) noexcept
        {
            return t * t * t;
        }

        constexpr float outCubic(float t) noexcept
        {
            return helpers::makeEaseOut(inCubic, t);
        }

        constexpr float inOutCubic(float t) noexcept
        {
            return helpers::makeEaseInOut(inCubic, t);
        }

        constexpr float inQuart(float t) noexcept
        {
            return t * t * t * t;
        }

        constexpr float outQuart(float t) noexcept
        {
            return helpers::makeEaseOut(inQuart, t);
        }

        constexpr float inOutQuart(float t) noexcept
        {
            return helpers::makeEaseInOut(inQuart, t);
        }

        constexpr float inQuint(float t) noexcept
        {
            return t * t * t * t * t;
        }

        constexpr float outQuint(float t) noexcept
        {
            return helpers::makeEaseOut(inQuint, t);
        }

        constexpr float inOutQuint(float t) noexcept
        {
            return helpers::makeEaseInOut(inQuint, t);
        }

        constexpr float inSextic(float t) noexcept
        {
            return t * t * t * t * t * t;
        }

        constexpr float outSextic(float t) noexcept
        {
            return helpers::makeEaseOut(inSextic, t);
        }

        constexpr float inOutSextic(float t) noexcept
        {
            return helpers::makeEaseInOut(inSextic, t);
        }

        constexpr float inSeptic(float t) noexcept
        {
            return t * t * t * t * t * t * t;
        }

        constexpr float outSeptic(float t) noexcept
        {
            return helpers::makeEaseOut(inSeptic, t);
        }

        constexpr float inOutSeptic(float t) noexcept
        {
            return helpers::makeEaseInOut(inSeptic, t);
        }

        constexpr float inOctic(float t) noexcept
        {
            return t * t * t * t * t * t * t * t;
        }

        constexpr float outOctic(float t) noexcept
        {
            return helpers::makeEaseOut(inOctic, t);
        }

        constexpr float inOutOctic(float t) noexcept
        {
            return helpers::makeEaseInOut(inOctic, t);
        }

        constexpr float inNonic(float t) noexcept
        {
            return t * t * t * t * t * t * t * t * t;
        }

        constexpr float outNonic(float t) noexcept
        {
            return helpers::makeEaseOut(inNonic, t);
        }

        constexpr float inOutNonic(float t) noexcept
        {
            return helpers::makeEaseInOut(inNonic, t);
        }

        constexpr float inDecic(float t) noexcept
        {
            return t * t * t * t * t * t * t * t * t * t;
        }

        constexpr float outDecic(float t) noexcept
        {
            return helpers::makeEaseOut(inDecic, t);
        }

        constexpr float inOutDecic(float t) noexcept
        {
            return helpers::makeEaseInOut(inDecic, t);
        }

        class inPoly
        {
        private:
            float _degree;

        public:
            constexpr explicit inPoly(float degree) noexcept : _degree(degree)
            {
            }

            constexpr float operator()(float normalizedTime) const noexcept
            {
                return std::pow(normalizedTime, _degree);
            }
        };

        class outPoly
        {
        private:
            inPoly _in;

        public:
            constexpr explicit outPoly(float degree) noexcept : _in(degree) {}
            constexpr float operator()(float normalizedTime) const noexcept
            {
                return helpers::makeEaseOut(_in, normalizedTime);
            }
        };

        class inOutPoly
        {
        private:
            inPoly _in;

        public:
            constexpr explicit inOutPoly(float degree) noexcept : _in(degree) {}
            constexpr float operator()(float normalizedTime) const noexcept
            {
                return helpers::makeEaseInOut(_in, normalizedTime);
            }
        };

        // Smoothstep (no in and out, they are always S shape)
        constexpr float smoothStep(float normalizedTime) noexcept
        {
            return normalizedTime * normalizedTime *
                   (3.f - 2.f * normalizedTime);
        }

        constexpr float smootherStep(float normalizedTime) noexcept
        {
            return normalizedTime * normalizedTime * normalizedTime *
                   (normalizedTime * (normalizedTime * 6 - 15) + 10);
        }

        // Trigonometric
        constexpr float inSine(float normalizedTime) noexcept
        {
            return 1.0f - std::cos(normalizedTime *
                                   (std::numbers::pi_v<float> * 0.5f));
        }

        constexpr float outSine(float normalizedTime) noexcept
        {
            return helpers::makeEaseOut(inSine, normalizedTime);
        }

        constexpr float inOutSine(float normalizedTime) noexcept
        {
            return helpers::makeEaseInOut(inSine, normalizedTime);
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
        constexpr float inCirc(float normalizedTime) noexcept
        {
            return 1.0f - std::sqrtf(1.0f - normalizedTime * normalizedTime);
        }

        constexpr float outCirc(float normalizedTime) noexcept
        {
            return helpers::makeEaseOut(inCirc, normalizedTime);
        }

        constexpr float inOutCirc(float normalizedTime) noexcept
        {
            return helpers::makeEaseInOut(inCirc, normalizedTime);
        }

        // Back
        constexpr float inBack(float normalizedTime) noexcept
        {
            constexpr float c1 = 1.70158f;
            constexpr float c3 = c1 + 1.0f;

            return c3 * normalizedTime * normalizedTime * normalizedTime -
                   c1 * normalizedTime * normalizedTime;
        }

        constexpr float outBack(float normalizedTime) noexcept
        {
            return helpers::makeEaseOut(inBack, normalizedTime);
        }

        constexpr float inOutBack(float normalizedTime) noexcept
        {
            return helpers::makeEaseInOut(inBack, normalizedTime);
        }

        // Physical
        constexpr float inElastic(float normalizedTime) noexcept
        {
            if (normalizedTime == 0.0f)
                return 0.0f;
            if (normalizedTime == 1.0f)
                return 1.0f;

            // Periodieke constante voor de elasticiteitsgolf: c4 = (2 * PI) / 3
            constexpr float c4 = (2.0f * std::numbers::pi_v<float>) / 3.0f;

            // Exponentiële groei gecombineerd met de sinusgolf
            float exp = std::pow(2.0f, 10.0f * normalizedTime - 10.0f);
            float sin = std::sin((10.0f * normalizedTime - 10.75f) * c4);

            return -(exp * sin);
        }

        constexpr float outElastic(float normalizedTime) noexcept
        {
            return helpers::makeEaseOut(inElastic, normalizedTime);
        }

        constexpr float inOutElastic(float normalizedTime) noexcept
        {
            return helpers::makeEaseInOut(inElastic, normalizedTime);
        }

        constexpr float outBounce(float normalizedTime) noexcept
        {
            constexpr float n1 = 7.5625f;
            constexpr float d1 = 2.75f;

            if (normalizedTime < 1.0f / d1)
            {
                return n1 * normalizedTime * normalizedTime;
            }
            else if (normalizedTime < 2.0f / d1)
            {
                float t = normalizedTime - (1.5f / d1);
                return n1 * t * t + 0.75f;
            }
            else if (normalizedTime < 2.625f / d1)
            {
                float t = normalizedTime - (2.25f / d1);
                return n1 * t * t + 0.9375f;
            }
            else
            {
                float t = normalizedTime - (2.625f / d1);
                return n1 * t * t + 0.984375f;
            }
        }

        constexpr float inBounce(float normalizedTime) noexcept
        {
            return 1.0f - outBounce(1.0f - normalizedTime);
        }

        constexpr float inOutBounce(float normalizedTime) noexcept
        {
            return helpers::makeEaseInOut(inBounce, normalizedTime);
        }
    } // namespace easing
} // namespace math