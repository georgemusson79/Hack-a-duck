#ifndef E74718CC_2856_4B82_836B_D43F8A28905B
#define E74718CC_2856_4B82_836B_D43F8A28905B

#include <vector>

#include "../UserInterface/Button.h"
#include "../UserInterface/Texture.h"

class Menu {
    private:
        bool exitMenu = false;
        Texture* bg;
        Texture* path;
        std::vector<Button> buttons;

        SDL_Rect* menuRect = new SDL_Rect{800,0,200,800};

        // Rounds
        bool roundStarted = false;
        int roundNumber = 1;
        int roundReward = 250;

    public:
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

            buttons.push_back(Button("../resources/justbutten.png",
                                     {805, 720, 75, 75}, [this]{roundStarted = true;}));
            buttons[1].MakeHidden(true);
        }

        void Display() {
            bg->render();
            path->render();

            SDL_SetRenderDrawColor(window->GetRenderer(), 0, 120, 30, 255);
            SDL_RenderFillRect(window->GetRenderer(), menuRect);

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
            buttons[1].MakeHidden(false);
            exitMenu = true;
        }

        int EndRound() {
            roundStarted = false;
            roundNumber++;
            int r = roundReward;
            roundReward = int((float)roundReward * 1.28);
            return r;
        }

        [[nodiscard]] bool MenuClosed() const { return exitMenu;};
        [[nodiscard]] bool RoundStarted() const { return roundStarted; };
};

#endif
