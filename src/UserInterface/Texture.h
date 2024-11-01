#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

#include "MainWindow.h"
#include "Vector2.h"

class Texture {
   protected:
    SDL_Texture* texture = nullptr;
    std::string path;

   public:
    int x;
    int y;
    int w;
    int h;
    int rx;
    int ry;
    int rw;
    int rh;
    double rotation = 0;
    void deleteTexture() {
        SDL_DestroyTexture(texture);
    }

    Vector2 getCenter() {
        return Vector2(this->x + (this->w / 2), this->y + (this->y / 2));
    }

    void setPath(std::string path) {
        this->path = path;
        this->deleteTexture();
        auto s = IMG_Load(path.c_str());
        this->texture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        if (!this->texture) std::cerr << "fucked\n";
    }

    std::string getPath() {
        return this->path;
    }

    Texture(const std::string& path, int x, int y, int w, int h) {
        this->setPath(path);
        this->x = x;
        this->w = w;
        this->h = h;
        this->y = y;
    }

    void render() {
        SDL_Rect dstrect = {x, y, w, h};
        SDL_RenderCopy(window->GetRenderer(), this->texture, NULL, NULL);
        // SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, this->rotation, NULL, SDL_FLIP_NONE);
    }

    void render(int sx, int sy, int sw, int sh) {
        SDL_Rect dstrect = {x, y, w, h};
        SDL_Rect srcrect = {sx, sy, sw, sh};
        SDL_RenderCopyEx(window->GetRenderer(), texture, &srcrect, &dstrect, this->rotation, NULL, SDL_FLIP_NONE);
    }

    ~Texture() {
        this->deleteTexture();
    }
};
