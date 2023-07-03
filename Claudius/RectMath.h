#pragma once
#include "CoreIncludes.h"
#include "Vector2.h"

namespace RectMath
{
    static Vector2 RectPos(const Rect& rect) noexcept
    {
        return { static_cast<float>(rect.x), static_cast<float>(rect.y) };
    }

    static Vector2 Delta(const Rect& lhs, const Rect& rhs) noexcept
    {
        return RectPos(lhs) - RectPos(rhs);
    }

    static float Distance(const Rect& lhs, const Rect& rhs) noexcept
    {
        return Vector2::length(Delta(lhs, rhs));
    }

    static Vector2 Direction(const Rect& lhs, const Rect& rhs) noexcept
    {
        return Vector2::normalize(Delta(lhs, rhs));
    }

    static void PlaceRect(Rect& rect, const Vector2& position) noexcept
    {
        rect.x = static_cast<int>(std::roundf(position.x));
        rect.y = static_cast<int>(std::roundf(position.y));
    }

    static Point RectCenter(const Rect& rect) noexcept
    {
        return { rect.x + rect.w / 2, rect.y + rect.h / 2 };
    }
}