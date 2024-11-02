//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_DUCK_H
#define HACK_A_DUCK_DUCK_H

#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include <string>
#include <vector>

#include "../UserInterface/Mouse.h"
#include "Cat.h"
#include "Player.h"

class BreadCrumbProjectile;

class Duck {
   private:
    // image
    std::string imgPath = "resources/chick.png";
    SDL_Texture* duckTexture;
    SDL_Rect* duckRect = new SDL_Rect{0, 0, 40, 40};
    bool showRedError = false;
    int shoddyTimer = 0;

    // projectiles
    std::vector<std::unique_ptr<BreadCrumbProjectile>> breadCrumbs;
    GenericCat* target{};
    float radius = 200;
    int dmg = 1;

    Uint64 attackTimer = 800;
    Uint64 ticksSinceLastAttack = 0;

    // abilities
    static int cost;
    std::string displayName{"Basic Bread-Lobbing Duck"};
    int catCount{0};

   public:
    Duck();

    void Display();
    void FindTarget();
    void AttackTarget(Uint64 _deltaTicks);
    void Update();

    static Duck* DuckAtMouse(float _mouseRadius);
    static void PlaceDuck();
    void SetDuckPosition(SDL_Rect _rect);

    [[nodiscard]] int GetDamage() const { return dmg; };
    [[nodiscard]] int GetCost() const { return cost; };
};

inline int Duck::cost = 125;

inline std::vector<std::unique_ptr<Duck>> playerDucks;
inline std::unique_ptr<Duck> displayDuck;

inline void DisplayDuckMode() {
    DUCK d = player->HoldingDuck();

    switch (d) {
        case DUCK::BASIC:
            displayDuck = std::make_unique<Duck>();
            break;

        default:  // DUCK::NONE
            displayDuck.reset();
    }

    if (displayDuck != nullptr) {
        auto [x, y] = mouse->GetPosition();
        displayDuck->SetDuckPosition({x, y, 40, 40});
        displayDuck->Display();
    }
}

class BreadCrumbProjectile {
   private:
    Texture* t;
    std::string imgPath = "resources/bread.png";
    SDL_Texture* breadTexture{};
    SDL_Rect breadRect{};

    GenericCat* target;
    double x = 0, y = 0;
    double spd = 0.3;
    bool hitTarget = false;

    Duck* parentDuck{};

   public:
    BreadCrumbProjectile(Duck* _parent, GenericCat* _target, SDL_Rect _origin);

    void MoveToTarget();
    void Display();

    [[nodiscard]] bool HitTarget() const { return hitTarget; };
};

#endif  // HACK_A_DUCK_DUCK_H
