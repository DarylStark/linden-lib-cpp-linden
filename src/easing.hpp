#pragma once

#include <cstdint>
#include <memory>

namespace math
{
    namespace easing
    {
        class EasingStrategy
        {
        public:
            using UniquePtr = std::unique_ptr<EasingStrategy>;

        public:
            virtual ~EasingStrategy() = default;
            virtual float apply(float normalizedTime) noexcept = 0;
        };

        class Linear : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutQuad : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutSmoothStep : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutSmootherStep : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutSine : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutBack : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutCubic : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutElastic : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutBounce : public EasingStrategy
        {
        private:
            float _easeOutBounce(float normalizedTime) noexcept;

        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutQuart : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutQuint : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutExpo : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutCirc : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutSextic : public EasingStrategy
        {
        public:
            float apply(float normalizedTime) noexcept override;
        };

        class InOutPoly : public EasingStrategy
        {
        private:
            float _degree;

        public:
            InOutPoly(float degree = 1.0f) noexcept;
            float apply(float normalizedTime) noexcept override;
        };
    } // namespace easing
} // namespace math