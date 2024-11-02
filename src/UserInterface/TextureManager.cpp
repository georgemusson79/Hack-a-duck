//
// Created by cew05 on 02/11/2024.
//

#include "TextureManager.h"
#include "MainWindow.h"

TextureManager::~TextureManager() {
    for (auto& pair : pathTextureMap) {
        SDL_DestroyTexture(pair.second);
    }
}

SDL_Texture* TextureManager::GetTexture(const std::string &_path) {
    if (pathTextureMap.count(_path) > 0)
        return pathTextureMap.find(_path)->second;

    // make new texture
    auto s = IMG_Load(_path.c_str());
    pathTextureMap[_path] = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
    return pathTextureMap.find(_path)->second;
}