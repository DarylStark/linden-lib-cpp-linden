# Ease-in-out transition formulas

> What other formula's for ease-in-out are there?

There are many.

The two you have are both quadratic-ish choices:

- `EaseInOutQuad` is a piecewise quadratic curve.
- `SmoothStep` is a cubic polynomial that behaves similarly.

Other common ease-in-out formulas include:

- `EaseInOutSine`  
  Uses a cosine shape for a very soft start/end:
  $$
  f(t) = -\frac{\cos(\pi t) - 1}{2}
  $$

- `EaseInOutCubic`  
  Stronger acceleration/deceleration than quadratic:
  $$
  f(t) =
  \begin{cases}
  4t^3 & t < 0.5 \\
  1 - \frac{(-2t + 2)^3}{2} & t \ge 0.5
  \end{cases}
  $$

- `EaseInOutQuart` and `EaseInOutQuint`  
  Even steeper in the middle, increasingly dramatic.

- `Smoothstep` variants  
  `smootherstep` is a quintic polynomial:
  $$
  f(t) = t^3( t( t\cdot 6 - 15 ) + 10 )
  $$
  It has even smoother derivatives at the ends than `smoothstep`.

- `EaseInOutExpo`  
  Very slow at the ends, very fast in the middle.

- `EaseInOutBack`  
  Goes slightly past the endpoint and comes back, for a more playful motion.

- `EaseInOutElastic`  
  Oscillates like a spring.

- `EaseInOutBounce`  
  Mimics bouncing motion.

If you want a practical next step, I’d suggest trying these three in order:
1. `EaseInOutSine` for a gentle, natural feel
2. `EaseInOutCubic` for a bit more motion
3. `SmootherStep` if you want a very smooth graphics-style transition
