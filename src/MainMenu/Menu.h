#ifndef E74718CC_2856_4B82_836B_D43F8A28905B
#define E74718CC_2856_4B82_836B_D43F8A28905B

#include <vector>

#include "../UserInterface/Button.h"

class Menu {
   public:
        std::vector<Button> buttons;
    void update();
    Menu();
}

#endif /* E74718CC_2856_4B82_836B_D43F8A28905B */
