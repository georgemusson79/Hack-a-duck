#ifndef C2418716_F499_4A05_875C_908D63ED3D84
#define C2418716_F499_4A05_875C_908D63ED3D84

#include "../UserInterface/Texture.h"
#include "Path.h"

class GenericCat {
   protected:
    int PathWidth = 1000 / 20;

   public:
    Texture t;
    int health = 100;
    int speed = 1;
    Path currentPath;

    void hurt(int dmg) {
    }

    void moveToNextPath() {
        currentPath;
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
};

inline std::vector<std::unique_ptr<GenericCat>> cats;

#endif /* C2418716_F499_4A05_875C_908D63ED3D84 */
