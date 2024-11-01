#ifndef E74718CC_2856_4B82_836B_D43F8A28905B
#define E74718CC_2856_4B82_836B_D43F8A28905B

#include <vector>

#include "../UserInterface/Button.h"
#include "../UserInterface/Texture.h"

void startGame() {
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
        int w = 200;
        int h = 150;
        int x = 400 - (w / 2);
        int y = 400 - (h / 2);
        this->buttons.push_back(Button("../resources/StartButten.png", {x, y, w, h}, startGame));
    }

    void Display() {
        bg->render();
    }
};

#endif
