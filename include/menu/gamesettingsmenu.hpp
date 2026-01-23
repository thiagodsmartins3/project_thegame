#ifndef GAMESETTINGSMENU_HPP
#define GAMESETTINGSMENU_HPP

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <iostream>

class GameSettingsMenu {
    public:
        struct ResMode {
            int w, h;
            std::string label;
        };

    public:
        GameSettingsMenu();
        void applySettings(SDL_Window* window, SDL_Renderer* renderer);
        void nextResolution();

    private:
        std::vector<ResMode> availableModes;
        int selectedIdx;
};

#endif