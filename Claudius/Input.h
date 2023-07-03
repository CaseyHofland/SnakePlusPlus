#pragma once
#include "CoreIncludes.h"
#include <vector>

struct InputData
{
private:
    std::vector<Uint8> currentFrame{};
    std::vector<Uint8> lastFrame{};

public:
    InputData(const std::vector<Uint8>& currentFrame, const std::vector<Uint8>& lastFrame) noexcept : currentFrame{ currentFrame }, lastFrame{ lastFrame } {}

    [[gsl::suppress(26812, justification : "The warning is thrown by the third party SDL library.")]]
    bool GetKey(Scancode scancode) const noexcept
    {
        return scancode < currentFrame.size()
            && currentFrame.at(scancode);
    }

    bool GetKeyDown(Scancode scancode) const noexcept
    {
        return GetKey(scancode)
            && (scancode >= lastFrame.size() || !lastFrame.at(scancode));
    }

    bool GetKeyUp(Scancode scancode) const noexcept
    {
        return !GetKey(scancode)
            && scancode < lastFrame.size()
            && lastFrame.at(scancode);
    }
};

struct InputManager
{
private:
    std::vector<Uint8> currentFrame{};
    std::vector<Uint8> lastFrame{};

public:
    InputData GenerateInputData() noexcept
    {
        lastFrame = currentFrame;

        SDL_PumpEvents();
        int numKeys;
        auto keyboard = SDL_GetKeyboardState(&numKeys);

        [[gsl::suppress(bounds.1, justification: "The warning is thrown by the third party SDL library.")]]
        currentFrame = { keyboard, keyboard + numKeys };

        return { currentFrame, lastFrame };
    }
};