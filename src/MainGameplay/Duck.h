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

#include "../UserInterface/Button.h"
#include "../UserInterface/Mouse.h"
#include "Cat.h"
#include "Player.h"

class BreadCrumbProjectile;

class Duck {
   private:
    // image
    std::string baselvl = "../resources/chick.png";
    SDL_Texture* duckTexture;
    SDL_Rect* duckRect = new SDL_Rect{0, 0, 40, 40};
    SDL_Rect* srcRect{nullptr};
    bool showRedError = false;
    int shoddyTimer = 0;

    // projectiles
    std::vector<std::unique_ptr<BreadCrumbProjectile>> breadCrumbs;
    std::vector<GenericCat*> targets{};
    float radius = 200;
    int dmg = 1;

    Uint64 attackTimer = 800;
    Uint64 ticksSinceLastAttack = 0;

    // abilities
    static int baseCost;
    int lvl = 1;
    int upgradeCost = baseCost + 70;
    bool showUpgWindow = false;
    std::string displayName{"Basic Bread-Lobbing Duck"};
    int catCount{0};

    TTF_Font* font = TTF_OpenFont("../resources/TCFR.ttf", 100);
    Button* upgButton = new Button("../resources/chick.png",
                                   {825, 75, 25, 25},
                                   [this] { Upgrade(); });
    SDL_Texture* labelTexture{};
    SDL_Texture* upgLabelTexture{};

   public:
    Duck();

    void Display();
    void FindTarget();
    void AttackTarget(Uint64 _deltaTicks);
    void Update(Uint64 _deltaTicks);

    // upgrades
    void ShowUpgradeWindow(bool _show);
    static Duck* DuckAtMouse(float _mouseRadius);
    static void PlaceDuck();
    void SetDuckPosition(SDL_Rect _rect);
    void Upgrade();

    void CheckButtons();

    [[nodiscard]] int GetDamage() const { return dmg; };
    [[nodiscard]] int GetCost() const { return baseCost; };
};

inline int Duck::baseCost = 125;
inline std::vector<std::unique_ptr<Duck>> playerDucks;
inline Duck* mouseHoverDuck{};
inline Duck* selectedDuck{};

inline std::unique_ptr<Duck> displayDuck;
inline DUCK lastDuck = DUCK::NONE;

inline void DisplayDuckMode() {
    DUCK d = player->HoldingDuck();

    if (lastDuck != d) {
        switch (d) {
            case DUCK::BASIC:
                displayDuck = std::make_unique<Duck>();
                break;

            default:  // DUCK::NONE
                displayDuck.reset();
        }
        lastDuck = d;
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
    std::string imgPath = "../resources/bread.png";
    SDL_Texture* breadTexture{};
    SDL_Rect breadRect{};

    GenericCat* target;
    double x = 0, y = 0;
    double spd = 300;
    bool hitTarget = false;

    Uint64 decayTime = 100;

    Duck* parentDuck{};

    friend class Duck;

   public:
    BreadCrumbProjectile(Duck* _parent, GenericCat* _target, SDL_Rect _origin);

    void MoveToTarget(Uint64 _deltaTicks);
    void Display();

    [[nodiscard]] bool HitTarget() const { return hitTarget; };
};

#endif  // HACK_A_DUCK_DUCK_H
