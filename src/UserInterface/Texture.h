

#ifndef TEXTUREHEADER_H
#define TEXTUREHEADER_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

#include "../MainGameplay/Vector2.h"
#include "MainWindow.h"

class Texture {
   protected:
    SDL_Texture* texture = nullptr;
    std::string path;

   public:
    SDL_Rect* r = new SDL_Rect();
    int rx;
    int ry;
    int rw;
    int rh;
    double rotation = 0;

    void deleteTexture() {
        SDL_DestroyTexture(texture);
    }

    Vector2 getCenter() {
        return Vector2(r->x + (r->w / 2), r->y + (r->y / 2));
    }

    std::string getPath() {
        return this->path;
    }

    Texture(const std::string& path, int x, int y, int w, int h) {
        this->path = path;

        auto s = IMG_Load(path.c_str());
        texture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_FreeSurface(s);

        r->x = x;
        r->w = w;
        r->h = h;
        r->y = y;
    }

    void render() {
        SDL_RenderCopyEx(window->GetRenderer(), this->texture, NULL, r, this->rotation, NULL, SDL_FLIP_NONE);
        // SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, this->rotation, NULL, SDL_FLIP_NONE);
    }

    void render(int sx, int sy, int sw, int sh) {
        SDL_Rect srcrect = {sx, sy, sw, sh};
        SDL_RenderCopyEx(window->GetRenderer(), texture, &srcrect, r, this->rotation, NULL, SDL_FLIP_NONE);
    }

    ~Texture() {
        this->deleteTexture();
    }
};

#endif
// esfionsfioshfoisfobisibfosboiufsbiuofbiuosEfbiuosfiobsbiuofdsbgeiu
