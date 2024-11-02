//
// Created by cew05 on 01/11/2024.
//

#include "Duck.h"
#include "../UserInterface/Mouse.h"
#include "../UserInterface/MainWindow.h"

Duck::Duck() {
    duckRect = new SDL_Rect{150,150,50,50};

    auto s = IMG_Load(imgPath.c_str());
    duckTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void Duck::Display() {
    if (showRedError) {
        SDL_Rect r = *duckRect;
        r.w *= 2;
        r.h *= 2;
        r.x -= duckRect->w/2;
        r.y -= duckRect->h/2;

        auto s = IMG_Load("../resources/red (1).png");
        auto t = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_RenderCopy(window->GetRenderer(), t, nullptr, &r);
        shoddyTimer++;
        if (shoddyTimer > 50) {
            showRedError = false;
            shoddyTimer = 0;
        }
    }

    SDL_RenderCopy(window->GetRenderer(), duckTexture, nullptr, duckRect);

    for (const auto& crumb : breadCrumbs) {
        crumb->Display();
    }
}


// determine if a cat position is within duck range, and lock on to it
void Duck::FindTarget() {
    for (const auto& cat : cats) {
        int x = cat->catRect->x - duckRect->x + 25;
        int y = cat->catRect->y - duckRect->y + 25;

        if (float(x*x) + float(y*y) < radius*radius){
            target = cat.get();
            return;
        }
    }

    // target lost
    target = nullptr;
}

void Duck::AttackTarget(Uint64 _deltaTicks) {
    ticksSinceLastAttack += _deltaTicks;

    if (target == nullptr) {
        if (ticksSinceLastAttack > attackTimer) ticksSinceLastAttack = attackTimer;
        return;
    }

    if (ticksSinceLastAttack >= attackTimer) {
        ticksSinceLastAttack -= attackTimer;

        // throw projectile at target
        SDL_Rect origin = *duckRect;
        origin.w = 40;
        origin.h = 40;
        breadCrumbs.push_back(std::make_unique<BreadCrumbProjectile>(this, target, origin));
    }
}


void Duck::Update() {
    for (auto bc = breadCrumbs.begin(); bc != breadCrumbs.end();) {
        if (bc->get()->HitTarget()) {
            bc = breadCrumbs.erase(bc);
            continue; // next bc
        }

        // otherwise
        bc->get()->MoveToTarget();
        bc++;
    }
}


Duck* Duck::DuckAtMouse(float _mouseRadius) {
    for (const auto& duck : playerDucks) {
        int x = duck->duckRect->x - mouse->GetPosition().first +25;
        int y = duck->duckRect->y - mouse->GetPosition().second +25;

        if (float(x*x) + float(y*y) < _mouseRadius*_mouseRadius) return duck.get();
    }

    return nullptr;
}

void Duck::PlaceDuck() {
    if (!mouse->IsUnheldActive()) return;

    // is space occupied by another duck?
    Duck* duck;
    if ((duck = DuckAtMouse(50)) != nullptr) {
        duck->showRedError = true;
        return;
    }

    // Money Check
    if (player->GetMoney() < cost) return;

    // place a duck at the mouse position
    auto [x, y] = mouse->GetPosition();
    std::unique_ptr<Duck> d = std::make_unique<Duck>();

    d->duckRect = new SDL_Rect{x-25, y-25, 50, 50};
    playerDucks.push_back(std::move(d));

    player->AddMoney(-cost);
}





BreadCrumbProjectile::BreadCrumbProjectile(Duck* _parent, GenericCat *_target, SDL_Rect _origin) {
    parentDuck = _parent;
    target = _target;
    breadRect = _origin;
    x = breadRect.x;
    y = breadRect.y;

    auto s = IMG_Load(imgPath.c_str());
    breadTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void BreadCrumbProjectile::MoveToTarget() {
    if (hitTarget) return;

    // Distance to target
    int distX = target->GetRect()->x - breadRect.x;
    int distY = target->GetRect()->y - breadRect.y;

    // Check for collision
    if (std::abs(distX) < 2 && std::abs(distY) < 2 ) {
        target->TakeDamage(parentDuck->GetDamage());
        hitTarget = true; // dissapear now
        return;
    }

    // Move to target
    x += spd * ((distX < 0) ? -1 : 1);
    y += spd * ((distY < 0) ? -1 : 1);

    breadRect.x = (int)x;
    breadRect.y = (int)y;
}


void BreadCrumbProjectile::Display() {
    SDL_Rect src{0,0,192,140};
    SDL_RenderCopy(window->GetRenderer(), breadTexture, &src, &breadRect);
}