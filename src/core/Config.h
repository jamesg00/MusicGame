#pragma once
#include <vector>

namespace Config {
    constexpr int ScreenWidth = 400;
    constexpr int ScreenHeight = 600;
    constexpr int TargetFPS = 60;
    constexpr double FrameDuration = 1.0 / TargetFPS;

    constexpr int HitY = 525;

    // Using a function or extern for Lanes if we want to avoid static initialization order issues,
    // but for simple vector it's fine in header if inline or static.
    // Since C++17, we can use inline variables.
    inline const std::vector<int> Lanes = {59, 137, 215, 293};

    constexpr double NoteSpeed = 300.0; // Pixels per second default
    constexpr int NoteWidth = 20;
    constexpr int NoteHeight = 20;
}
