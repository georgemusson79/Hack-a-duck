//
// Created by cew05 on 01/11/2024.
//

#include "Duck.h"

#include <SDL_ttf.h>

#include "../UserInterface/MainWindow.h"
#include "../UserInterface/Mouse.h"
#include "../UserInterface/Sound.h"
Duck::~Duck() {
    delete this->upgButton;
    SDL_DestroyTexture(this->upgLabelTexture);
    SDL_DestroyTexture(duckTexture);
}
Duck::Duck() {
    spawnSnd1 = std::make_unique<Sound>("../resources/placeDuckSFX1.wav");
    shootSnd1 = std::make_unique<Sound>("../resources/duckShoot1.wav");
    shootSnd1->setVolume(30);
    duckRect = new SDL_Rect{150, 150, 50, 50};

    auto s = IMG_Load(baselvl.c_str());
    duckTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);

    SDL_Color c{255, 255, 255, 255};
    s = TTF_RenderText_Blended(font, displayName.c_str(), c);
    labelTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);

    s = TTF_RenderText_Blended(font, "<- 150 coins!", c);
    upgLabelTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void Duck::Display() {
    if (showRedError) {
        SDL_Rect r = *duckRect;
        r.w *= 2;
        r.h *= 2;
        r.x -= duckRect->w / 2;
        r.y -= duckRect->h / 2;

        auto s = IMG_Load("../resources/red (1).png");
        auto t = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_RenderCopy(window->GetRenderer(), t, nullptr, &r);
        SDL_FreeSurface(s);
        SDL_DestroyTexture(t);
        shoddyTimer++;
        if (shoddyTimer > 50) {
            showRedError = false;
            shoddyTimer = 0;
        }
    }

    SDL_RenderCopy(window->GetRenderer(), duckTexture, srcRect, duckRect);

    for (const auto& crumb : breadCrumbs) {
        crumb->Display();
    }

    if (!showUpgWindow) return;
    // show upgrade window:

    SDL_Rect r{812, 25, 175, 25};
    SDL_RenderCopy(window->renderer, labelTexture, nullptr, &r);

    r = SDL_Rect{863, 75, 125, 25};
    SDL_RenderCopy(window->renderer, upgLabelTexture, nullptr, &r);

    upgButton->Display();
}

void Duck::ShowUpgradeWindow(bool _show) {
    upgButton->MakeHidden(!_show);
    showUpgWindow = _show;
};

// determine if a cat position is within duck range, and lock on to it
void Duck::FindTarget() {
    targets.clear();

    for (const auto& cat : cats) {
        int x = cat->catRect->x - duckRect->x + 25;
        int y = cat->catRect->y - duckRect->y + 25;

        if (float(x * x) + float(y * y) < radius * radius) {
            targets.push_back(cat.get());
            if (targets.size() > lvl) return;
        }

        if (targets.size() >= lvl) break;
    }
}

void Duck::AttackTarget(Uint64 _deltaTicks) {
    ticksSinceLastAttack += _deltaTicks;

    if (targets.empty()) {
        if (ticksSinceLastAttack > attackTimer) ticksSinceLastAttack = attackTimer;
        return;
    }

    if (ticksSinceLastAttack >= attackTimer) {
        ticksSinceLastAttack -= attackTimer;

        for (auto& target : targets) {
            // throw projectile at target
            this->shootSnd1->play();
            SDL_Rect origin = *duckRect;
            origin.w = 40;
            origin.h = 40;
            breadCrumbs.push_back(std::make_unique<BreadCrumbProjectile>(this, target, origin));
        }

        for (auto& crumb : breadCrumbs) {
            if (crumb->target == nullptr) crumb->target = targets.back();
        }
    }
}

void Duck::Update(Uint64 _deltaTicks) {
    for (auto bc = breadCrumbs.begin(); bc != breadCrumbs.end();) {
        if (bc->get()->HitTarget()) {
            bc = breadCrumbs.erase(bc);
            continue;  // next bc
        }

        // otherwise
        bc->get()->MoveToTarget(_deltaTicks);
        bc++;
    }
}

Duck* Duck::DuckAtMouse(float _mouseRadius) {
    for (const auto& duck : playerDucks) {
        int x = duck->duckRect->x - mouse->GetPosition().first + 25;
        int y = duck->duckRect->y - mouse->GetPosition().second + 25;

        if (float(x * x) + float(y * y) < _mouseRadius * _mouseRadius) {
            mouseHoverDuck = duck.get();
            return duck.get();
        }
    }

    mouseHoverDuck = nullptr;
    return nullptr;
}

void Duck::PlaceDuck() {
    if (!mouse->IsUnheldActive()) return;

    DUCK pd = player->HoldingDuck();
    if (pd == DUCK::NONE) return;  // not duck placing mode

    // is space occupied by another duck?
    if (mouseHoverDuck != nullptr) {
        mouseHoverDuck->showRedError = true;
        return;
    }

    // Money Check
    if (player->GetMoney() < baseCost) return;

    // place a duck at the mouse position
    auto [x, y] = mouse->GetPosition();
    std::unique_ptr<Duck> d = std::make_unique<Duck>();
    d->spawnSnd1->play();

    d->duckRect = new SDL_Rect{x - 25, y - 25, 50, 50};
    playerDucks.push_back(std::move(d));

    player->AddMoney(-baseCost);
}

void Duck::SetDuckPosition(SDL_Rect _rect) {
    duckRect = new SDL_Rect(_rect);
}

void Duck::Upgrade() {
    if (selectedDuck != this) return;
    if (player->GetMoney() < baseCost) return;

    player->AddMoney(-baseCost);
    upgradeCost += 70;

    // apply upgrades
    dmg++;
    attackTimer -= 50;
    lvl++;

    SDL_Color c{255, 255, 255, 255};
    std::string str = "<- " + std::to_string(upgradeCost) + " Coins!";
    auto s = TTF_RenderText_Blended(font, str.c_str(), c);
    upgLabelTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);

    // upgrade duck model
    std::string modelPath;
    switch (lvl) {
        case 2:
            modelPath = "../resources/helmetDuckSheet.png";
            srcRect = new SDL_Rect{304, 0, 304, 224};
            break;

        case 3:
            modelPath = "../resources/ArmoredDuckSheet.png";
            srcRect = new SDL_Rect{304, 0, 304, 224};
            break;

        case 4:
            modelPath = "../resources/BlackGooseling.png";
            srcRect = new SDL_Rect{0, 0, 304, 224};
            break;

        case 5:
            modelPath = "../resources/BlackHelmetGoose.png";
            srcRect = new SDL_Rect{0, 0, 304, 256};
            break;

        default:
            modelPath = "../resources/BlackArmoredGoose.png";
            srcRect = new SDL_Rect{0, 0, 304, 287};
            break;
    }

    s = IMG_Load(modelPath.c_str());
    duckTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void Duck::CheckButtons() {
    upgButton->CheckClick();
}

BreadCrumbProjectile::BreadCrumbProjectile(Duck* _parent, GenericCat* _target, SDL_Rect _origin) {
    parentDuck = _parent;
    target = _target;
    breadRect = _origin;
    x = breadRect.x;
    y = breadRect.y;

    auto s = IMG_Load(imgPath.c_str());
    breadTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
    SDL_FreeSurface(s);
}

void BreadCrumbProjectile::MoveToTarget(Uint64 _deltaTicks) {
    if (hitTarget || target == nullptr) {
        decayTime -= _deltaTicks;
        if ((int)decayTime < 0) {
            hitTarget = true;
        }
        return;
    }

    // Distance to target
    if (target->IsDead()) {
        target = nullptr;
        return;
    }
    int distX = target->GetRect()->x - breadRect.x;
    int distY = target->GetRect()->y - breadRect.y;

    // Check for collision
    if (std::abs(distX) < 2 && std::abs(distY) < 2) {
        target->TakeDamage(parentDuck->GetDamage());
        hitTarget = true;  // dissapear now
        return;
    }

    // Move to target
    x += spd * (_deltaTicks / 1000.0) * ((distX < 0) ? -1 : 1);
    y += spd * (_deltaTicks / 1000.0) * ((distY < 0) ? -1 : 1);

    breadRect.x = (int)x;
    breadRect.y = (int)y;
}

void BreadCrumbProjectile::Display() {
    if (hitTarget) return;
    SDL_Rect src{0, 0, 192, 140};
    SDL_RenderCopy(window->GetRenderer(), breadTexture, &src, &breadRect);
}