#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class FontManager {
public:
    ~FontManager();

    TTF_Font* Load(const std::string& key, const std::string& path, int size);
    TTF_Font* Get(const std::string& key);
    void Clean();

private:
    std::unordered_map<std::string, TTF_Font*> mFonts;
};
