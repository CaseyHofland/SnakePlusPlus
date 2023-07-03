#include "Game.h"

void Game::Update(float deltaTime, const InputData& input) noexcept
{
    m_snake.Update(deltaTime, input);
    m_snake.TryEatApple(m_apple);
}

void Game::Render(const Renderer& renderer) const noexcept
{
    // Clear the screen.
    renderer.Clear();

    // Draw Renderers.
    m_snake.Render(renderer);
    m_apple.Render(renderer);

    // Render.
    renderer.Render();
}

void Game::Run() noexcept
{
    bool running{ true };
    do 
    {
        // Update systems.
        m_time.Update();
        const auto& input = m_inputManager.GenerateInputData();

        // Update and Render objects.
        Update(m_time.GetDeltaTime(), input);
        Render(m_renderer);

        running = !input.GetKey(Scancode::SDL_SCANCODE_ESCAPE);
    } while (running);
}