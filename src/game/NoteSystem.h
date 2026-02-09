#pragma once
#include <vector>
#include <list>
#include <SDL3/SDL.h>
#include "assets/TextureManager.h"
#include "core/Config.h"

struct ActiveNote {
    int lane;
    double hitTime; // Seconds
    bool active;
};

class NoteSystem {
public:
    void Spawn(int lane, double hitTime);
    void Update(double songTime);
    void Render(SDL_Renderer* renderer, TextureManager* textureManager, double songTime);
    bool CheckHit(int lane, double songTime);
    void Reset();

private:
    struct ActiveNote {
        int lane;
        double hitTime;
        bool active;
    };
    std::list<ActiveNote> mNotes;
    const double mHitWindow = 0.15; // 150ms
};
