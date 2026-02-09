#include "GameState.h"
#include "MenuState.h"
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "core/Config.h"

GameState::GameState(Context* context) : mContext(context), mSongTime(0), mNextNoteIndex(0) {}

GameState::~GameState() {}

void GameState::Enter() {
    std::cout << "Entering Game State" << std::endl;
    if (!mChart.Load("json/level.json")) {
        std::cerr << "Failed to load level!" << std::endl;
    }
    mNoteSystem.Reset();
    mScoring.Reset();
    mSongTime = 0;
    mNextNoteIndex = 0;
}

void GameState::Exit() {
    std::cout << "Exiting Game State" << std::endl;
}

void GameState::Update(double dt) {
    mSongTime += dt;

    // Spawn notes ahead of time
    const double spawnAheadTime = 2.0; // seconds
    const auto& notes = mChart.GetNotes();

    while (mNextNoteIndex < notes.size()) {
        const auto& note = notes[mNextNoteIndex];
        if (note.time <= mSongTime + spawnAheadTime) {
            mNoteSystem.Spawn(note.lane, note.time);
            mNextNoteIndex++;
        } else {
            break;
        }
    }

    mNoteSystem.Update(mSongTime);
}

void GameState::Render() {
    if (!mContext || !mContext->renderer) return;

    // Draw Hit Line
    SDL_SetRenderDrawColor(mContext->renderer, 100, 100, 100, 255);
    SDL_FRect lineRect = {0, (float)Config::HitY, (float)Config::ScreenWidth, 2};
    SDL_RenderFillRect(mContext->renderer, &lineRect);

    // Render Notes
    mNoteSystem.Render(mContext->renderer, mContext->textureManager.get(), mSongTime);

    // Render Score
    TTF_Font* font = mContext->fontManager->Load("default", "assets/upheavtt.ttf", 24);
    if (font) {
        std::string scoreText = "Score: " + std::to_string(mScoring.GetScore());
        SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {10, 10, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }

        std::string comboText = "Combo: " + std::to_string(mScoring.GetCombo());
        surface = TTF_RenderText_Solid(font, comboText.c_str(), 0, {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(mContext->renderer, surface);
            if (texture) {
                SDL_FRect dst = {10, 40, (float)surface->w, (float)surface->h};
                SDL_RenderTexture(mContext->renderer, texture, NULL, &dst);
                SDL_DestroyTexture(texture);
            }
            SDL_DestroySurface(surface);
        }
    }
}

void GameState::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
             mContext->stateMachine->ChangeState(std::make_unique<MenuState>(mContext));
             return;
        }

        // Check for hits
        int lane = -1;
        if (event.key.key == SDLK_A) lane = 0;
        else if (event.key.key == SDLK_S) lane = 1;
        else if (event.key.key == SDLK_D) lane = 2;
        else if (event.key.key == SDLK_F) lane = 3;

        if (lane != -1) {
            if (mNoteSystem.CheckHit(lane, mSongTime)) {
                mScoring.AddHit(true);
            } else {
                // Optional: Penalize spamming
            }
        }
    }
}
