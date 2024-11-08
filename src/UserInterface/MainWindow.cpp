//
// Created by cew05 on 01/11/2024.
//
#include "MainWindow.h"

MainWindow::MainWindow() {
    window = SDL_CreateWindow("Ducks Bread Defence",
                              0, 0, 1000, 800,
                              SDL_RENDERER_ACCELERATED);

    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED);

    SDL_SetWindowPosition(window, 50, 50);
}

void MainWindow::Display() {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}
