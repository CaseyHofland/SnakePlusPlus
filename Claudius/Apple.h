#pragma once
#include "CoreIncludes.h"
#include "Renderer.h"
#include "Grid.h"

struct Apple
{
public:
	Rect bounds{ Grid::RandTile() };
	Color color{ Core::appleColor };

	void Render(const Renderer& renderer) const noexcept
	{
		renderer.FillRect(color, bounds);
	}
};