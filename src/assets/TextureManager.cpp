#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* renderer) : mRenderer(renderer) {}

TextureManager::~TextureManager() {
    Clean();
}

SDL_Texture* TextureManager::Load(const std::string& key, const std::string& path) {
    if (mTextures.count(key)) {
        return mTextures[key];
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image " << path << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture from " << path << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    mTextures[key] = texture;
    return texture;
}

SDL_Texture* TextureManager::Get(const std::string& key) {
    if (mTextures.count(key)) {
        return mTextures[key];
    }
    return nullptr;
}

void TextureManager::Clean() {
    for (auto& pair : mTextures) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    mTextures.clear();
}
