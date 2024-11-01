#ifndef E74718CC_2856_4B82_836B_D43F8A28905B
#define E74718CC_2856_4B82_836B_D43F8A28905B

#include <vector>

#include "../UserInterface/Button.h"
#include "../UserInterface/Texture.h"

void fn() {
    std::cout << "b";
}

class Menu {
   public:
    Texture* bg;
    std::vector<Button> buttons;
    void update() {
        this->bg->render();
        for (auto& button : this->buttons) {
            button.Display();
            button.CheckClick();
        }
    }
    Menu() {
        this->bg = new Texture("../resources/mapback.png", 0, 0, 800, 800);
        this->buttons.push_back(Button("../resources/StartButten.png", {250, 500, 500, 200}, fn));
    }
};

#endif
