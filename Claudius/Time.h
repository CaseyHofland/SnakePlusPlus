#pragma once
#include "CoreIncludes.h"

class Time
{
private:
    float m_time{};
    float m_deltaTime{};

    Uint64 m_now{ SDL_GetPerformanceCounter() };
    Uint64 m_last{};

public:
    void Update() noexcept
    {
        m_last = m_now;
        m_now = SDL_GetPerformanceCounter();

        m_deltaTime = ((m_now - m_last) * 1000.0f / SDL_GetPerformanceFrequency()) * 0.001f;
        m_time += m_deltaTime;
    }

    float GetTime() const noexcept
    {
        return m_time;
    }

    float GetDeltaTime() const noexcept
    {
        return m_deltaTime;
    }
};
