#ifndef HACK_A_DUCK_MENU_H
#define HACK_A_DUCK_MENU_H

#include <SDL.h>

#include <memory>

#include "../UserInterface/Texture.h"

class Menu {
   private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};

   public:
    Menu();

    void Display();

    [[nodiscard]] SDL_Window* GetWindow() const { return window; }
    [[nodiscard]] SDL_Renderer* GetRenderer() const { return renderer; }
};

inline std::unique_ptr<Menu> window;

#endif  // HACK_A_DUCK_MENU_H
