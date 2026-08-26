#pragma once

#include "helpers.hpp"
#include <cmath>
#include <cstddef>
#include <numbers>

namespace linden::math
{
    namespace easing
    {

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
                float x = t - (1.5f / d1); // GEFIXED: 't' gebruikt i.p.v. 'x'
                return n1 * x * x + 0.75f;
            }
            else if (t < 2.625f / d1)
            {
                float x = t - (2.25f / d1); // GEFIXED: 't' gebruikt i.p.v. 'x'
                return n1 * x * x + 0.9375f;
            }
            else
            {
                float x = t - (2.625f / d1); // GEFIXED: 't' gebruikt i.p.v. 'x'
                return n1 * x * x + 0.984375f;
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
} // namespace linden::math
