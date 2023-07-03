#pragma once

#include <limits>

/*
=======================================
            NOTE TO ULF
=======================================

I realize my Vector2 implementation is way out of proportion. I copied the class from my previous attempt in which I had a lot of code in a lot of places, to which I made a lot of improvements. However, considering the standalone nature of Vector2, it felt equally pointless to remove its functionality, since none of the other code would particularly gain any clarity from that, so I decided to leave it in and focus on the more important parts of the code base.
*/

struct Vector2
{
	// Variables
	float x{};
	float y{};

	// Predefined Values
	static constexpr Vector2 zero() noexcept { return { 0.0f, 0.0f }; }
	static constexpr Vector2 one() noexcept { return { 1.0f, 1.0f }; }
	static constexpr Vector2 right() noexcept { return { 1.0f, 0.0f }; }
	static constexpr Vector2 left() noexcept { return -right(); }
	static constexpr Vector2 up() noexcept { return { 0.0f, 1.0f }; }
	static constexpr Vector2 down() noexcept { return -up(); }
	static constexpr Vector2 positiveInfinity() noexcept { return { std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() }; }
	static constexpr Vector2 negativeInfinity() noexcept { return -positiveInfinity(); }

	// Constructors
	Vector2() = default;
	constexpr Vector2(float x, float y) noexcept;

	// (Binary) Arithmatic operators
	constexpr Vector2 operator+() const noexcept { return { +x, +y }; }
	constexpr Vector2 operator-() const noexcept { return { -x, -y }; }

	Vector2& operator+=(const Vector2& rhs) noexcept;					// compound assignment (does not need to be a member, but often is, to modify the private members)
	friend Vector2 operator+(Vector2 lhs, const Vector2& rhs) noexcept;	// friends defined inside class body are inline and are hidden from non-ADL lookup

	Vector2& operator-=(const Vector2& rhs) noexcept;
	friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) noexcept;

	Vector2& operator*=(const Vector2& rhs) noexcept;
	Vector2& operator*=(const float& rhs) noexcept;						// we do not need to pass float by reference here, however we do so as to conform to the implementation pattern
	friend Vector2 operator*(Vector2 lhs, const Vector2& rhs) noexcept;
	friend Vector2 operator*(Vector2 lhs, const float& rhs) noexcept;
	friend Vector2 operator*(const float& lhs, Vector2 rhs) noexcept;

	Vector2& operator/=(const Vector2& rhs) noexcept;
	Vector2& operator/=(const float& rhs) noexcept;
	friend Vector2 operator/(Vector2 lhs, const Vector2& rhs) noexcept;
	friend Vector2 operator/(Vector2 lhs, const float& rhs) noexcept;
	friend Vector2 operator/(const float& lhs, Vector2 rhs) noexcept;

	// Comparison operators
	bool operator==(const Vector2& rhs) const noexcept;
	bool operator!=(const Vector2& rhs) const noexcept;

	// Static functions
	static Vector2 perpendicular(const Vector2& vector2) noexcept;
	static float length(const Vector2& vector2) noexcept;
	static float length_squared(const Vector2& vector2) noexcept;
	static Vector2 normalize(const Vector2& vector2) noexcept;
};