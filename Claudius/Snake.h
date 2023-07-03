#pragma once
#include "CoreIncludes.h"
#include <vector>
#include "Vector2.h"
#include "Grid.h"
#include "Input.h"
#include "Apple.h"
#include "Renderer.h"

class Snake
{
private:
	static constexpr unsigned minimumBodyParts{ 3 };

	Vector2 m_position{};
	Vector2 m_moveDirection{};
	std::vector<Rect> m_bodyParts{};

	void ProcessInput(const InputData& input) noexcept;
	void Snap() noexcept;
	void UpdateBodyPosition() noexcept;
	bool HasBodyCollision() const noexcept;

public:
	Color bodyColor{ Core::snakeBodyColor };
	Color headColor{ Core::snakeHeadColor };
	float speed{ Core::startingSpeed };

	Snake() noexcept;

	void Update(float deltaTime, const InputData& input) noexcept;
	void Render(const Renderer& renderer) const noexcept;

	const auto& Head() const noexcept
	{
		return m_bodyParts.front();
	}

	const auto& Tail() const noexcept
	{
		return m_bodyParts.back();
	}

	void Grow() noexcept
	{
		try 
		{
			m_bodyParts.push_back({ static_cast<int>(m_position.x), static_cast<int>(m_position.y), Grid::tileSize, Grid::tileSize });
		}
		catch (...) 
		{
			// Unknown exception caused Snake::Grow() to fail. Preventing the snake from growing to keep the game running.
		}
	}

	void Shrink() noexcept
	{
		if (m_bodyParts.size() <= minimumBodyParts)
		{
			return;
		}

		m_bodyParts.pop_back();
	}

	void EatApple(Apple& apple) noexcept
	{
		Grow();
		speed += Core::appleSpeedIncrease;

		apple = {};
	}

	bool TryEatApple(Apple& apple) noexcept
	{
		if (SDL_HasIntersection(&Head(), &apple.bounds))
		{
			EatApple(apple);
			return true;
		}

		return false;
	}

	void Die() noexcept
	{
		*this = {};
	}
};