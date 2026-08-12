#pragma once

#include "helpers.hpp"

namespace math
{
    namespace easing
    {
        // Generic
        constexpr float linear(float t) noexcept
        {
            return t;
        }

        constexpr float step(float t) noexcept
        {
            return t < 0.5f ? 0.0f : 1.0f;
        }

        constexpr float smoothStep(float t) noexcept
        {
            return t * t * (3.f - 2.f * t);
        }

        constexpr float smootherStep(float t) noexcept
        {
            return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
        }
    } // namespace easing
} // namespace math
