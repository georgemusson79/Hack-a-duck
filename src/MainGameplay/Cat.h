#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include "../UserInterface/Texture.h"
#include "Path.h"

class GenericCat {
   protected:
    SDL_Rect* catRect{};
    std::string imgPath{"../resources/redcat1.png"};
    SDL_Texture* catTexture;
    //            int PathWidth = 1000 / 20;

    int health = 100;
    int speed = 1;

    friend class Duck;

   public:
    GenericCat();

    void hurt(int dmg);
    void moveToNextPath();
    void die();
    void dealDmgToPlayer();
    void setRotation(double rot);

    void Display();
    void update();

    //        [[nodiscard]] double getRotation() {return this->t.rotation;}
};

inline std::vector<std::unique_ptr<GenericCat>> cats;

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
