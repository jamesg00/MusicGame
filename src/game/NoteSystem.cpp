#include "NoteSystem.h"
#include <iostream>
#include <cmath>

void NoteSystem::Spawn(int lane, double hitTime) {
    mNotes.push_back({lane, hitTime, true});
}

void NoteSystem::Update(double songTime) {
    auto it = mNotes.begin();
    while (it != mNotes.end()) {
        if (!it->active) {
            it = mNotes.erase(it);
            continue;
        }

        // Check if note missed (passed hit window)
        // If songTime > hitTime + window, it's a miss
        if (songTime > it->hitTime + mHitWindow) {
            // Missed
            it = mNotes.erase(it);
        } else {
            ++it;
        }
    }
}

void NoteSystem::Render(SDL_Renderer* renderer, TextureManager* textureManager, double songTime) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (const auto& note : mNotes) {
        if (!note.active) continue;

        // noteTime - songTime > 0 means note is in future (above HitY)
        // y = HitY - (futureTime - currentTime) * speed
        // If noteTime = songTime + 1s, speed = 100px/s, HitY = 500
        // y = 500 - (1) * 100 = 400. Correct (falling down).

        double y = Config::HitY - (note.hitTime - songTime) * Config::NoteSpeed;

        SDL_FRect rect = {
            (float)Config::Lanes[note.lane],
            (float)y,
            (float)Config::NoteWidth,
            (float)Config::NoteHeight
        };

        if (y > -50 && y < Config::ScreenHeight + 50) {
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

bool NoteSystem::CheckHit(int lane, double songTime) {
    // Check notes in the given lane
    // Find the closest one within window
    ActiveNote* closest = nullptr;
    double minDiff = mHitWindow;

    for (auto& note : mNotes) {
        if (note.lane == lane && note.active) {
            double diff = std::abs(songTime - note.hitTime);
            if (diff <= minDiff) {
                minDiff = diff;
                closest = &note;
            }
        }
    }

    if (closest) {
        closest->active = false; // Mark as hit, will be removed in Update
        return true;
    }
    return false;
}

void NoteSystem::Reset() {
    mNotes.clear();
}
