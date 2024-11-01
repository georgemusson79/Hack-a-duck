#include <Menu.h>

/**
 * @brief Creates the Main Menu
 **/ 
Menu::Menu() {
    window = SDL_CreateWindow("Ducks Bread Defence",
                              0, 0, 500, 500,
                              SDL_RENDERER_ACCELERATED);

    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED);

    SDL_SetWindowPosition(window, 50, 50);
}

/**
 * @brief Displays the Main Menu to your screen
 **/
void Menu::Display() {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

