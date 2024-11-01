//
// Created by cew05 on 01/11/2024.
//
#include "MainWindow.h"

MainWindow::MainWindow() {
    window = SDL_CreateWindow("Ducks Bread Defence",
                              0, 0, 500, 500,
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

void MainWindow::renderTextures() {
    for (auto pair : this->textures) {
        pair.second.render();
    }
}
