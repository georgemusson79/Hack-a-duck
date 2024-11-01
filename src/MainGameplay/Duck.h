//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_DUCK_H
#define HACK_A_DUCK_DUCK_H

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>
#include <memory>

class BreadCrumbProjectile;

class Duck {
    private:
        // image
        std::string imgPath = "../resources/chick.png";
        SDL_Texture* duckTexture;
        SDL_Rect* duckRect;

        // projectiles
//        std::vector<std::unique_ptr<BreadCrumbProjectile>> breadCrumbs;
        float radius = 5;

        // abilities
        std::string displayName {"Basic Bread-Lobbing Duck"};
        int catCount {0};

    public:
        Duck();

        void Display();
        void FindTarget();

        static void PlaceDuck();
};

inline std::vector<std::unique_ptr<Duck>> playerDucks;

class BreadCrubProjectile {
    private:
        std::string imgPath = "../resources/chick.png";
        SDL_Texture* breadTexture;
        SDL_Rect* breadRect;

    public:

};

#endif //HACK_A_DUCK_DUCK_H
