#pragma once
#include "CoreIncludes.h"
#include "SDLSystem.h"
#include "Window.h"
#include "Renderer.h"
#include "Time.h"
#include "Apple.h"
#include "Snake.h"
#include "Input.h"

class Game
{
private:
    SDLSystem m_sdl{ SDL_INIT_EVERYTHING };
    Window m_window{ Grid::width, Grid::height };
    Renderer m_renderer{ m_window };

    Time m_time{};
    InputManager m_inputManager{};

    Apple m_apple{};
    Snake m_snake{};

public:
    void Update(float deltaTime, const InputData& input) noexcept;
    void Render(const Renderer& renderer) const noexcept;
    void Run() noexcept;
};