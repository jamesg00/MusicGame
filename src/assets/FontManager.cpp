#include "FontManager.h"
#include <iostream>

FontManager::~FontManager() {
    Clean();
}

TTF_Font* FontManager::Load(const std::string& key, const std::string& path, int size) {
    if (mFonts.count(key)) {
        return mFonts[key];
    }

    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font " << path << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    mFonts[key] = font;
    return font;
}

TTF_Font* FontManager::Get(const std::string& key) {
    if (mFonts.count(key)) {
        return mFonts[key];
    }
    return nullptr;
}

void FontManager::Clean() {
    for (auto& pair : mFonts) {
        if (pair.second) {
            TTF_CloseFont(pair.second);
        }
    }
    mFonts.clear();
}
