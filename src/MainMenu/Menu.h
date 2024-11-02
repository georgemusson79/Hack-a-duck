#ifndef E74718CC_2856_4B82_836B_D43F8A28905B
#define E74718CC_2856_4B82_836B_D43F8A28905B

#include <vector>

#include "../UserInterface/Button.h"
#include "../UserInterface/Texture.h"

class Menu {
   private:
    bool exitMenu = false;
    Texture* bg;
    Texture* overlay;
    Texture* path;
    Texture* title;
    std::vector<Button> buttons;

    SDL_Rect* menuRect = new SDL_Rect{800, 0, 200, 800};

    SDL_Texture* roundLabel {};

    // Rounds
    bool roundStarted = false;
    int roundNumber = 1;
    int roundReward = 250;
    int ty = 50;
    int endy;

   public:
    Menu() {
        TTF_Font* font = TTF_OpenFont("../resources/TCFR.ttf", 100);
        int twidth = 800 / 1.5;
        int theight = 300;
        int tx = (800 / 2) - (twidth / 2);
        int tyStart = -theight - 50;
        this->title = new Texture("../resources/title2.png", tx, tyStart, twidth, theight);
        this->bg = new Texture("../resources/mapback.png", 0, 0, 800, 800);
        this->overlay = new Texture("../resources/overlay.png", 0, 0, 800, 800);
        path = new Texture("../resources/Path.png", 0, 0, 800, 800);
        int w = 200;
        int h = 150;
        int x = 400 - (w / 2);
        int y = 800 + h;
        endy = 400 - (h / 2);
        this->buttons.push_back(Button("../resources/red button.png",
                                       {x, y, w, h},
                                       [this] { Start(); }));

        buttons.push_back(Button("../resources/justbutten.png",
                                 {805, 720, 75, 75}, [this] { roundStarted = true; }));
        buttons[1].MakeHidden(true);

        std::string str {"Start Round " + std::to_string(roundNumber)};
        auto s = TTF_RenderText_Blended(font, str.c_str(), {255, 255, 255, 255});
        roundLabel = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_FreeSurface(s);
    }

    void Display() {
        if (title->r->y != ty) title->r->y += 2;
        if (this->buttons[0].getRect().y > endy) {
            SDL_Rect r = this->buttons[0].getRect();
            r.y -= 2;
            this->buttons[0].setRect(r);
        }
        bg->render();
        path->render();
        if (!exitMenu) title->render();

        SDL_SetRenderDrawColor(window->GetRenderer(), 0, 120, 30, 255);
        SDL_RenderFillRect(window->GetRenderer(), menuRect);

        for (auto& button : this->buttons) {
            button.Display();
            button.CheckClick();
        }
        if (exitMenu) {
            SDL_Rect r{812, 675, 175, 25};
            SDL_RenderCopy(window->GetRenderer(), roundLabel, nullptr, &r);
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

        // update round label
        std::string str {"Start Round " + std::to_string(roundNumber)};
        TTF_Font* font = TTF_OpenFont("../resources/TCFR.ttf", 100);
        auto s = TTF_RenderText_Blended(font, str.c_str(), {255, 255, 255, 255});
        roundLabel = SDL_CreateTextureFromSurface(window->GetRenderer(), s);
        SDL_FreeSurface(s);

        return r;
    }

    void ReturnToMenu() {
        exitMenu = false;
        buttons[1].MakeHidden(true);
        buttons[0].MakeHidden(false);
    }

    [[nodiscard]] bool MenuClosed() const { return exitMenu; };
    [[nodiscard]] bool RoundStarted() const { return roundStarted; };
    [[nodiscard]] int GetLevel() const { return roundNumber; };
};

#endif
