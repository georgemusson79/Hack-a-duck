#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include "../UserInterface/Texture.h"
#include "Path.h"
#include "Player.h"

class GenericCat {
    protected:
        // positioning
        double x, y;
        SDL_Rect* catRect{};

        // texture
        std::string imgPath{"../resources/redcat1.png"};
        SDL_Texture* catTexture;

        // inc with difficulty? change per type
        int health = 1;
        double spd {0.1};

        // pathfinding
        Node* currPathNode {};

        friend class Duck;

    public:
        GenericCat();

        void Display();

        void TakeDamage(int dmg);
        void MoveToNode();
        void setRotation(double rot);

        [[nodiscard]] SDL_Rect* GetRect() const { return catRect; };
        [[nodiscard]] bool IsDead() const { return health <= 0; };
        [[nodiscard]] bool ReachedEnd() const { return currPathNode == nullptr; };
        //        [[nodiscard]] double getRotation() {return this->t.rotation;}
};

inline std::vector<std::unique_ptr<GenericCat>> cats;

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
