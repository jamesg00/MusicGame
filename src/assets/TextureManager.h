#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    SDL_Texture* Load(const std::string& key, const std::string& path);
    SDL_Texture* Get(const std::string& key);
    void Clean();

private:
    SDL_Renderer* mRenderer;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
};
