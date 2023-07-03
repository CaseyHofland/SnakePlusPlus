#pragma once
#include "CoreIncludes.h"
#include "Window.h"

// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r1-manage-resources-automatically-using-resource-handles-and-raii-resource-acquisition-is-initialization
struct Renderer
{
private:
    SDL_Renderer* m_sdl_renderer;

public:
    Renderer(const Window& window)
    {
        m_sdl_renderer = SDL_CreateRenderer(window.GetPtr(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
        if (m_sdl_renderer == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    ~Renderer() noexcept
    {
        SDL_DestroyRenderer(m_sdl_renderer);
    }

    auto* GetPtr() const noexcept
    {
        return m_sdl_renderer;
    }

    Renderer(const Renderer&) = default;
    Renderer(Renderer&&) = default;
    Renderer& operator=(const Renderer&) = default;
    Renderer& operator=(Renderer&&) = default;

    void Clear(const Color& color = {}) const noexcept
    {
        SDL_SetRenderDrawColor(m_sdl_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(m_sdl_renderer);
    }

    void FillRect(const Color& color, const Rect& rect) const noexcept
    {
        SDL_SetRenderDrawColor(m_sdl_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(m_sdl_renderer, &rect);
    }

    void Render() const noexcept
    {
        SDL_RenderPresent(m_sdl_renderer);
    }
};
