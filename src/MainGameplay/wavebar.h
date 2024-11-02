#ifndef C0BE4B79_A3EF_4AF7_85F0_234685B83711
#define C0BE4B79_A3EF_4AF7_85F0_234685B83711
#include "Texture.h"

class WaveBar {
   protected:
    Texture* bg;
    Texture* bar;
    int health;
    int maxHealth;

   public:
    void setHealth(int health) {
        this->health = health;
        if (this->health < 0) this->health = 0;
        if (this->health > this->maxHealth) this->health = this->maxHealth;
    }

    void setMaxHealth(int health) {
        this->health = health;
        if (this->maxHealth < 0) this->maxHealth = 0;
        if (this->maxHealth < this->health) this->setHealth(this->maxHealth);
    }

    WaveBar(int health) {
    }
}

#endif /* C0BE4B79_A3EF_4AF7_85F0_234685B83711 */
