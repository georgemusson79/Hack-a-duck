#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include "../UserInterface/Texture.h"
#include "Path.h"

class GenericCat {
    protected:
        double x, y;
        double spd {0.1};
        SDL_Rect* catRect{};
        std::string imgPath{"../resources/redcat1.png"};
        SDL_Texture* catTexture;

        int health = 100;
        int speed = 1;

        Node* currPathNode {};

        friend class Duck;

    public:
        GenericCat();

        void Display();

        void hurt(int dmg);
        void moveToNextPath();
        void die() {printf("CAT IS DEAD\n");};
        void dealDmgToPlayer();
        void setRotation(double rot);

        void update();

        [[nodiscard]] SDL_Rect* GetRect() const { return catRect; };
        //        [[nodiscard]] double getRotation() {return this->t.rotation;}
};

inline std::vector<std::unique_ptr<GenericCat>> cats;

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
