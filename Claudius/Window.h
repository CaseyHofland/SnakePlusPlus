#pragma once
#include "CoreIncludes.h"

// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r1-manage-resources-automatically-using-resource-handles-and-raii-resource-acquisition-is-initialization
struct Window
{
private:
    SDL_Window* m_sdl_window;

public:
    Window(int width, int height)
    {
        m_sdl_window = SDL_CreateWindow(Core::title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WindowFlags::SDL_WINDOW_SHOWN);
        if (m_sdl_window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    ~Window() noexcept
    {
        SDL_DestroyWindow(m_sdl_window);
    }

    auto* GetPtr() const noexcept 
    { 
        return m_sdl_window; 
    }

    Window(const Window&) = default;
    Window(Window&&) = default;
    Window& operator=(const Window&) = default;
    Window& operator=(Window&&) = default;
};