//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_MAINWINDOW_H
#define HACK_A_DUCK_MAINWINDOW_H

#include <SDL.h>
#include <memory>

class MainWindow {
    private:
        SDL_Window* window {};
        SDL_Renderer* renderer {};

    public:
        MainWindow();



        [[nodiscard]] SDL_Window* GetWindow() const { return window; }
        [[nodiscard]] SDL_Renderer* GetRenderer() const { return renderer; }

        void Display();
};


#endif //HACK_A_DUCK_MAINWINDOW_H
