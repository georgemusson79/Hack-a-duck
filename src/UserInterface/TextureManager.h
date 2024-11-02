//
// Created by cew05 on 02/11/2024.
//

#ifndef HACK_A_DUCK_TEXTUREMANAGER_H
#define HACK_A_DUCK_TEXTUREMANAGER_H

#include <memory>
#include <unordered_map>
#include <SDL_image.h>

class TextureManager {
    private:
        std::unordered_map<std::string, SDL_Texture*> pathTextureMap;

    public:
        ~TextureManager();
        SDL_Texture* GetTexture(const std::string& _path);

};

inline std::unique_ptr<TextureManager> tm;

#endif //HACK_A_DUCK_TEXTUREMANAGER_H
