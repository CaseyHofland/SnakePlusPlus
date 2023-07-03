#pragma once
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include <string_view>
#include <stdexcept>
#include <random>

#include <iostream> // Used for debugging.

using namespace std::literals; // Writing using namespaces in global scope in a header file is bad practice, but the Core Guidelines make an exception for std::literals. https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf7-dont-write-using-namespace-at-global-scope-in-a-header-file

using Color = SDL_Color;
using Point = SDL_Point;
using Rect = SDL_Rect;
using Scancode = SDL_Scancode;

// Use a namespace to define global data. https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4459?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(C4459)%26rd%3Dtrue&view=msvc-170
namespace Core
{
    constexpr unsigned startingBodyParts{ 10 };
    constexpr float startingSpeed{ 10.0f };
    constexpr float appleSpeedIncrease{ 1.0f };
    constexpr std::string_view title{ "Snake" };

    constexpr Color appleColor{ 0, SDL_ALPHA_OPAQUE, 0, SDL_ALPHA_OPAQUE };
    constexpr Color snakeBodyColor{ SDL_ALPHA_OPAQUE , 0, 0, SDL_ALPHA_OPAQUE };
    constexpr Color snakeHeadColor{ 0, SDL_ALPHA_OPAQUE, 0, SDL_ALPHA_OPAQUE };

    // The Rand functions may throw an "unreferenced local function has been removed" warning if they are unused. However, since they're useful functions, we want to compile them regardless of if they're being used or not. https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4505?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(C4505)%26rd%3Dtrue&view=msvc-170
#pragma warning(disable:4505)
    /// <summary>
    /// Generates a random number between min (inclusive) and max (exclusive).
    /// </summary>
    static unsigned Rand(unsigned min, unsigned max) noexcept
    {
        if (max == 0)
        {
            return min;
        }

        try
        {
            // rand() is not recommended for serious random-number generation needs. It is recommended to use C++11's random number generation facilities to replace rand(). (since C++11) https://en.cppreference.com/w/cpp/numeric/random/rand
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<unsigned> dist(min, max - 1);

            return dist(mt);
        }
        catch (...)
        {
            //swallow the exception. No random number will be generated but the program keeps running.
            return {};
        }
    }

    /// <summary>
    /// Generates a random number below max (exclusive).
    /// </summary>
    static unsigned Rand(unsigned max) noexcept { return Rand(0, max); }

    /// <summary>
    /// Generates a random number.
    /// </summary>
    static unsigned Rand() noexcept { return Rand(UINT_MAX); }
#pragma warning(default:4505) 
}
