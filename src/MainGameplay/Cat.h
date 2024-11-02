#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include <cmath>

#include "../UserInterface/Texture.h"
#include "Path.h"

class GenericCat {
   protected:
    // positioning
    double x, y;
    SDL_Rect* catRect = new SDL_Rect{-100, 750, 50, 50};
    SDL_Rect* src = nullptr;

    // texture
    std::string imgPath{"../resources/redcat1.png"};
    SDL_Texture* catTexture{};

    // inc with difficulty? change per type
    int baseHp = 2;
    int health = baseHp;
    double spd{100.0};
    Uint64 waitTicks = 0;

    // pathfinding
    Node* currPathNode{};

    friend class Duck;

   public:
    GenericCat();

    void Display();

    void TakeDamage(int dmg);
    void MoveToNode(Uint64 _deltaTicks);
    void AddDelayBeforeMoving(Uint64 _ticksDelay);
    void MoveToRect(SDL_Rect _rect);
    void setRotation(double rot);

    [[nodiscard]] SDL_Rect* GetRect() const { return catRect; };
    [[nodiscard]] bool IsDead() const { return health <= 0; };
    [[nodiscard]] bool ReachedEnd() const { return currPathNode == nullptr; };
    //        [[nodiscard]] double getRotation() {return this->t.rotation;}
};

inline std::vector<std::unique_ptr<GenericCat>> cats;
inline bool catsSummoned = false;

// Sub Cats

class TankCat : public GenericCat {
    public:
        TankCat() : GenericCat() {
            baseHp = 5;
            health = baseHp;

            catRect->w = 60;
            catRect->h = 60;
            src = new SDL_Rect{0,0,512,512};

            imgPath = "../resources/lion.png";
            auto s = IMG_Load(imgPath.c_str());
            catTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
            SDL_FreeSurface(s);
        }
};

class MiniCat : public GenericCat {
    public:
        MiniCat() : GenericCat() {
            baseHp = 1;
            health = baseHp;

            src = new SDL_Rect{0,0,512,512};

            imgPath = "../resources/Ratos.png";
            auto s = IMG_Load(imgPath.c_str());
            catTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
            SDL_FreeSurface(s);
        }
};

inline void SummonCats(int _lvl) {
    int amplifier = (int)_lvl / 2;
    int delay = 500;
    int quantity = 25 + _lvl*5*amplifier;

    int tankQuantity = (int)pow(_lvl-1, 2)*amplifier;
    int tankDelay = delay*quantity;

    int miniQuantity = 15*(_lvl - 2)*amplifier/2;
    int miniDelay = 150;

    for (int c = 0; c < quantity; c++) {
        cats.push_back(std::make_unique<GenericCat>());
        cats.back()->AddDelayBeforeMoving(delay * c);
    }

    for (int c = 0; c < tankQuantity; c++) {
        cats.push_back(std::make_unique<TankCat>());
        cats.back()->AddDelayBeforeMoving(tankDelay / (c+1));
    }

    for (int c = 0; c < miniQuantity; c++) {
        cats.push_back(std::make_unique<MiniCat>());
        cats.back()->AddDelayBeforeMoving((miniDelay * c));
    }

    catsSummoned = true;
}

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
