#pragma once

#include <cstdint>
#include <memory>

namespace graphics
{
    class TweeningStrategy
    {
    public:
        using UniquePtr = std::unique_ptr<TweeningStrategy>;

    public:
        virtual ~TweeningStrategy() = default;
        virtual float apply(float normalizedTime) = 0;
    };

    class Linear : public TweeningStrategy
    {
    public:
        float apply(float normalizedTime) override;
    };

    class EaseInOutQuad : public TweeningStrategy
    {
    public:
        float apply(float normalizedTime) override;
    };

    class EaseInOutSmoothStep : public TweeningStrategy
    {
    public:
        float apply(float normalizedTime) override;
    };

    class EaseInOutSmootherStep : public TweeningStrategy
    {
    public:
        float apply(float normalizedTime) override;
    };

    class EaseInOutSine : public TweeningStrategy
    {
    public:
        float apply(float normalizedTime) override;
    };
} // namespace graphics