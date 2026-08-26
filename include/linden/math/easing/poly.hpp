#pragma once

#include "helpers.hpp"
#include <cstddef>

namespace linden::math
{
    namespace easing
    {
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

        class inPower
        {
        private:
            float _degree;

        public:
            constexpr explicit inPower(float degree) noexcept : _degree(degree)
            {
            }

            constexpr float operator()(float t) const noexcept
            {
                return std::pow(t, _degree);
            }
        };

        class outPower
        {
        private:
            inPower _in;

        public:
            constexpr explicit outPower(float degree) noexcept : _in(degree) {}
            constexpr float operator()(float t) const noexcept
            {
                return helpers::makeEaseOut(_in, t);
            }
        };

        class inOutPower
        {
        private:
            inPower _in;

        public:
            constexpr explicit inOutPower(float degree) noexcept : _in(degree)
            {
            }
            constexpr float operator()(float t) const noexcept
            {
                return helpers::makeEaseInOut(_in, t);
            }
        };
    } // namespace easing
} // namespace linden::math
