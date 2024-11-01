//
// Created by cew05 on 01/11/2024.
//

#ifndef HACK_A_DUCK_MOUSE_H
#define HACK_A_DUCK_MOUSE_H

#include <SDL.h>
#include <memory>

class Mouse {
    private:
        int x;
        int y;

        bool nextActive = false;
        bool active = false;
        bool prevactive = false;
        bool heldactive = false;

    public:
        void UpdatePosition() { SDL_GetMouseState(&x, &y); }

        bool InRect(SDL_Rect* _rect);
        bool UnheldClick(SDL_Rect* _rect);
        bool ClickOnRelease(SDL_Rect* _rect);

        [[nodiscard]] bool IsHeldActive() const {return active;}
        [[nodiscard]] bool IsUnheldActive() const {return active && !prevactive;}
};

inline std::unique_ptr<Mouse> mouse;

#endif //HACK_A_DUCK_MOUSE_H