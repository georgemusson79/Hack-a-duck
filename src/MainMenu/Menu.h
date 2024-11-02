#ifndef E74718CC_2856_4B82_836B_D43F8A28905B
#define E74718CC_2856_4B82_836B_D43F8A28905B

#include <vector>

#include "../UserInterface/Button.h"
#include "../UserInterface/Texture.h"

void startGame() {
    std::cout << "b";
}

class Menu {
    private:
        bool exitMenu = false;


   public:
    Texture* bg;
    Texture* path;
    std::vector<Button> buttons;
    Menu() {
        this->bg = new Texture("../resources/mapback.png", 0, 0, 800, 800);
        path = new Texture("../resources/Path.png", 0, 0, 800, 800);
        int w = 200;
        int h = 150;
        int x = 400 - (w / 2);
        int y = 400 - (h / 2);
        this->buttons.push_back(Button("../resources/StartButten.png",
                                       {x, y, w, h},
                                       [this]{Start();}));
    }

    void Display() {
        bg->render();
        path->render();

        for (auto& button : this->buttons) {
            button.Display();
            button.CheckClick();
        }
    }

    void CheckButtons() {
        for (auto& button : buttons) {
            button.CheckClick();
        }
    }

    void Start() {
        player->Setup();
        buttons[0].MakeHidden(true);
        exitMenu = true;
    }

    [[nodiscard]] bool MenuClosed() const { return exitMenu;};
};

#endif
