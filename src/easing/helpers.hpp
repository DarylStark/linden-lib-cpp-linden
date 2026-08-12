#pragma once

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
    } // namespace easing
} // namespace math