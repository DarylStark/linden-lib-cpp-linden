#pragma once

#include "helpers.hpp"
#include <cmath>
#include <cstddef>
#include <numbers>

namespace linden::math
{
    namespace easing
    {
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

        constexpr float inExpo(float t) noexcept
        {
            if (t == 0.0f)
                return 0.0f;
            return std::exp2(10.0f * t - 10.0f);
        }

        constexpr float outExpo(float t) noexcept
        {
            if (t == 1.0f)
            {
                return 1.0f;
            }
            return helpers::makeEaseOut(inExpo, t);
        }

        constexpr float inOutExpo(float t) noexcept
        {
            if (t == 0.0f)
            {
                return 0.0f;
            }
            if (t == 1.0f)
            {
                return 1.0f;
            }

            if (t < 0.5f)
            {
                return std::exp2(20.0f * t - 10.0f) / 2.0f;
            }

            return (2.0f - std::exp2(-20.0f * t + 10.0f)) / 2.0f;
        }

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
    } // namespace easing
} // namespace linden::math
