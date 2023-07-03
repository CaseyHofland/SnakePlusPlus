#pragma once
#include "CoreIncludes.h"

// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#r1-manage-resources-automatically-using-resource-handles-and-raii-resource-acquisition-is-initialization
struct SDLSystem
{
public:
    SDLSystem(unsigned flags)
    {
        const auto result = SDL_Init(flags);
        if (result != 0)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

    ~SDLSystem() noexcept
    {
        SDL_Quit();
    }

    SDLSystem(const SDLSystem&) = delete;
    SDLSystem(SDLSystem&&) = delete;
    SDLSystem& operator=(const SDLSystem&) = delete;
    SDLSystem& operator=(SDLSystem&&) = delete;
};