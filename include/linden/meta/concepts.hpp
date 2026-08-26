#pragma once

namespace linden::meta
{
    template <typename T>
    concept DurationLike = requires(const T &t) {
        typename T::rep;
        typename T::period;
        { t.count() };
    };
} // namespace linden::meta