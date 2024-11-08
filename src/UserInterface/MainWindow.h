//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_MAINWINDOW_H
#define HACK_A_DUCK_MAINWINDOW_H

#include <SDL.h>

#include <memory>
#include <unordered_map>
#include <vector>

class MainWindow {
   private:
    SDL_Window* window{};

   public:
    MainWindow();
    void Display();
    SDL_Renderer* renderer{};

    [[nodiscard]] SDL_Window* GetWindow() const { return window; }
    [[nodiscard]] SDL_Renderer* GetRenderer() const { return renderer; }
};

inline std::unique_ptr<MainWindow> window;

#endif  // HACK_A_DUCK_MAINWINDOW_H
