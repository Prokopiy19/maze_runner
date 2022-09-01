#include "render.hpp"

#include <cmath>

void Renderer::draw_ring(int cx, int cy, int rInner, int rOuter) const
{
    for (int x = cx - rOuter; x <= cx + rOuter; ++x)
        for (int y = cy - rOuter; y <= cy + rOuter; ++y) {
            int dist = std::hypot(x - cx, y - cy);
            if (rInner <= dist && dist <= rOuter)
                draw_point(x, y);
        }
}

void Renderer::draw_circle(int cx, int cy, int r) const
{
    draw_ring(cx, cy, 0, r);
}