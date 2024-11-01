#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

class Texture {
   protected:
    SDL_Texture* texture = nullptr;
    std::string path;
    SDL_Renderer* renderer;

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
    void setPath(std::string path) {
        this->path = path;
        this->deleteTexture();
        this->texture = IMG_LoadTexture(this->renderer, path.c_str());
    }

    std::string getPath() {
        return this->path;
    }

    Texture(SDL_Renderer* renderer, std::string path, int x, int y, int w, int h) {
        this->setPath(path);
        this->x = x;
        this->w = w;
        this->h = h;
        this->y = y;
    }

    void render() {
        SDL_Rect dstrect = {x, y, w, h};
        SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, this->rotation, NULL, SDL_FLIP_NONE);
    }

    void render(int sx, int sy, int sw, int sh) {
        SDL_Rect dstrect = {x, y, w, h};
        SDL_Rect srcrect = {sx, sy, sw, sh};
        SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, this->rotation, NULL, SDL_FLIP_NONE);
    }

    ~Texture() {
        this->deleteTexture();
    }
};
