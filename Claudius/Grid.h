#pragma once
#include "CoreIncludes.h"

namespace Grid
{
    constexpr unsigned tileSize{ 20 };
    constexpr unsigned columns{ 30 };
    constexpr unsigned rows{ 20 };
    constexpr unsigned width{ columns * tileSize };
    constexpr unsigned height{ rows * tileSize };

    constexpr static int Snap(int length) noexcept
    {
        return length / tileSize * tileSize;    // Use integer division to make the length snap to the grid (e.g. tileSize of 20 ensures the tile will always be divisable by 20).
    }

    static Rect RandTile() noexcept
    {
        return { Snap(Core::Rand(width)), Snap(Core::Rand(height)), tileSize, tileSize };
    }

    constexpr static bool OutOfBounds(const Rect& rect) noexcept
    {
        return rect.x < 0 || rect.x + rect.w > width
            || rect.y < 0 || rect.y + rect.h > height;
    }
}