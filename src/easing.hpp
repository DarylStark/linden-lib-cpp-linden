#pragma once

#include <cmath>
#include <cstdint>
#include <numbers>

namespace math
{
    namespace easing
    {
        namespace helpers
        {
            template <typename InFunc>
            constexpr float makeEaseOut(const InFunc &inFunc, float t) noexcept
            {
                return 1.0f - inFunc(1.0f - t);
            }

            template <typename InFunc>
            constexpr float makeEaseInOut(const InFunc &inFunc,
                                          float t) noexcept
            {
                if (t < 0.5f)
                {
                    return 0.5f * inFunc(t * 2.0f);
                }
                return 1.0f - 0.5f * inFunc(2.0f - 2.0f * t);
            }

        } // namespace helpers

        // Generic
        constexpr float linear(float t) noexcept
        {
            return t;
        }

        // Power easing In and Out
        template <std::size_t power>
        constexpr float inPoly(float t) noexcept
        {
            float result = 1.0f;
            for (std::size_t n = 0; n < power; n++)
            {
                result *= t;
            }
            return result;
        }

        template <std::size_t power>
        constexpr float outPoly(float t) noexcept
        {
            return helpers::makeEaseOut(inPoly<power>, t);
        }

        template <std::size_t power>
        constexpr float inOutPoly(float t) noexcept
        {
            return helpers::makeEaseInOut(inPoly<power>, t);
        }

        constexpr float inQuad(float t) noexcept
        {
            return inPoly<2>(t);
        }

        constexpr float outQuad(float t) noexcept
        {
            return outPoly<2>(t);
        }

        constexpr float inOutQuad(float t) noexcept
        {
            return inOutPoly<2>(t);
        }

        constexpr float inCubic(float t) noexcept
        {
            return inPoly<3>(t);
        }

        constexpr float outCubic(float t) noexcept
        {
            return outPoly<3>(t);
        }

        constexpr float inOutCubic(float t) noexcept
        {
            return inOutPoly<3>(t);
        }

        constexpr float inQuart(float t) noexcept
        {
            return inPoly<4>(t);
        }

        constexpr float outQuart(float t) noexcept
        {
            return outPoly<4>(t);
        }

        constexpr float inOutQuart(float t) noexcept
        {
            return inOutPoly<4>(t);
        }

        constexpr float inQuint(float t) noexcept
        {
            return inPoly<5>(t);
        }

        constexpr float outQuint(float t) noexcept
        {
            return outPoly<5>(t);
        }

        constexpr float inOutQuint(float t) noexcept
        {
            return inOutPoly<5>(t);
        }

        constexpr float inSextic(float t) noexcept
        {
            return inPoly<6>(t);
        }

        constexpr float outSextic(float t) noexcept
        {
            return outPoly<6>(t);
        }

        constexpr float inOutSextic(float t) noexcept
        {
            return inOutPoly<6>(t);
        }

        constexpr float inSeptic(float t) noexcept
        {
            return inPoly<7>(t);
        }

        constexpr float outSeptic(float t) noexcept
        {
            return outPoly<7>(t);
        }

        constexpr float inOutSeptic(float t) noexcept
        {
            return inOutPoly<7>(t);
        }

        constexpr float inOctic(float t) noexcept
        {
            return inPoly<8>(t);
        }

        constexpr float outOctic(float t) noexcept
        {
            return outPoly<8>(t);
        }

        constexpr float inOutOctic(float t) noexcept
        {
            return inOutPoly<8>(t);
        }

        constexpr float inNonic(float t) noexcept
        {
            return inPoly<9>(t);
        }

        constexpr float outNonic(float t) noexcept
        {
            return outPoly<9>(t);
        }

        constexpr float inOutNonic(float t) noexcept
        {
            return inOutPoly<9>(t);
        }

        constexpr float inDecic(float t) noexcept
        {
            return inPoly<10>(t);
        }

        constexpr float outDecic(float t) noexcept
        {
            return outPoly<10>(t);
        }

        constexpr float inOutDecic(float t) noexcept
        {
            return inOutPoly<10>(t);
        }

        class inPowerCurve
        {
        private:
            float _degree;

        public:
            constexpr explicit inPowerCurve(float degree) noexcept
                : _degree(degree)
            {
            }

            constexpr float operator()(float t) const noexcept
            {
                return std::pow(t, _degree);
            }
        };

        class outPowerCurve
        {
        private:
            inPowerCurve _in;

        public:
            constexpr explicit outPowerCurve(float degree) noexcept
                : _in(degree)
            {
            }
            constexpr float operator()(float t) const noexcept
            {
                return helpers::makeEaseOut(_in, t);
            }
        };

        class inOutPowerCurve
        {
        private:
            inPowerCurve _in;

        public:
            constexpr explicit inOutPowerCurve(float degree) noexcept
                : _in(degree)
            {
            }
            constexpr float operator()(float t) const noexcept
            {
                return helpers::makeEaseInOut(_in, t);
            }
        };

        // Steppers
        constexpr float smoothStep(float t) noexcept
        {
            return t * t * (3.f - 2.f * t);
        }

        constexpr float smootherStep(float t) noexcept
        {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        // Trigonometric
        constexpr float inSine(float t) noexcept
        {
            return 1.0f - std::cos(t * (std::numbers::pi_v<float> * 0.5f));
        }

        constexpr float outSine(float t) noexcept
        {
            return helpers::makeEaseOut(inSine, t);
        }

        constexpr float inOutSine(float t) noexcept
        {
            return helpers::makeEaseInOut(inSine, t);
        }

        // Exponental
        constexpr float inExpo(float t) noexcept
        {
            if (t == 0.0f)
                return 0.0f;
            return std::exp2(10.0f * t - 10.0f);
        }

        constexpr float outExpo(float t) noexcept
        {
            return helpers::makeEaseOut(inExpo, t);
        }

        constexpr float inOutExpo(float t) noexcept
        {
            return helpers::makeEaseInOut(inExpo, t);
        }

        // Circular
        constexpr float inCirc(float t) noexcept
        {
            return 1.0f - std::sqrt(1.0f - t * t);
        }

        constexpr float outCirc(float t) noexcept
        {
            return helpers::makeEaseOut(inCirc, t);
        }

        constexpr float inOutCirc(float t) noexcept
        {
            return helpers::makeEaseInOut(inCirc, t);
        }

        // Back
        constexpr float inBack(float t) noexcept
        {
            constexpr float c1 = 1.70158f;
            constexpr float c3 = c1 + 1.0f;

            return c3 * t * t * t - c1 * t * t;
        }

        constexpr float outBack(float t) noexcept
        {
            return helpers::makeEaseOut(inBack, t);
        }

        constexpr float inOutBack(float t) noexcept
        {
            return helpers::makeEaseInOut(inBack, t);
        }

        // Physical
        constexpr float inElastic(float t) noexcept
        {
            if (t == 0.0f)
                return 0.0f;
            if (t == 1.0f)
                return 1.0f;

            // Periodieke constante voor de elasticiteitsgolf: c4 = (2 * PI) / 3
            constexpr float c4 = (2.0f * std::numbers::pi_v<float>) / 3.0f;

            // Exponentiële groei gecombineerd met de sinusgolf
            float exp = std::pow(2.0f, 10.0f * t - 10.0f);
            float sin = std::sin((10.0f * t - 10.75f) * c4);

            return -(exp * sin);
        }

        constexpr float outElastic(float t) noexcept
        {
            return helpers::makeEaseOut(inElastic, t);
        }

        constexpr float inOutElastic(float t) noexcept
        {
            return helpers::makeEaseInOut(inElastic, t);
        }

        constexpr float outBounce(float t) noexcept
        {
            constexpr float n1 = 7.5625f;
            constexpr float d1 = 2.75f;

            if (t < 1.0f / d1)
            {
                return n1 * t * t;
            }
            else if (t < 2.0f / d1)
            {
                float t = t - (1.5f / d1);
                return n1 * t * t + 0.75f;
            }
            else if (t < 2.625f / d1)
            {
                float t = t - (2.25f / d1);
                return n1 * t * t + 0.9375f;
            }
            else
            {
                float t = t - (2.625f / d1);
                return n1 * t * t + 0.984375f;
            }
        }

        constexpr float inBounce(float t) noexcept
        {
            return 1.0f - outBounce(1.0f - t);
        }

        constexpr float inOutBounce(float t) noexcept
        {
            return helpers::makeEaseInOut(inBounce, t);
        }
    } // namespace easing
} // namespace math
