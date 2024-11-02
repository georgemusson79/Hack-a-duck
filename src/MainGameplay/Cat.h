#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include "../UserInterface/Texture.h"
#include "Path.h"

class GenericCat {
   protected:
    // positioning
    double x, y;
    SDL_Rect* catRect = new SDL_Rect{-100, 750, 50, 50};

    // texture
    std::string imgPath{"resources/redcat1.png"};
    SDL_Texture* catTexture{};

    // inc with difficulty? change per type
    int health = 1;
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

inline void SummonCats() {
    int delay = 500;
    int quantity = 25;

    for (int c = 0; c < quantity; c++) {
        cats.push_back(std::make_unique<GenericCat>());
        cats.back()->AddDelayBeforeMoving(delay * c);
    }

    catsSummoned = true;
}

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
