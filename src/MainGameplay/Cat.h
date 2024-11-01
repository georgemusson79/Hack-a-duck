#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include "../MainGameplay/Path.h"
#include "../UserInterface/Texture.h"

class GenericCat {
   protected:
    Texture t;
    Path p;

   public:
    int health = 100;

    void hurt(int dmg) {
    }

    void die() {
    }

    void dealDmgToPlayer() {
        }

    void setRotation(double rot) {
        this->t.rotation = rot;
    }

    double getRotation() {
        return this->t.rotation;
    }

    void Display() {
        this->t.render();
    }

    void update() {
    }
}

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
