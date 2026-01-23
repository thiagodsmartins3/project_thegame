#include "../../include/menu/gamesettingsmenu.hpp"

GameSettingsMenu::GameSettingsMenu() {
    int count = 0;
    selectedIdx = 0;
    SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
    SDL_DisplayMode** modes = SDL_GetFullscreenDisplayModes(displayID, &count);

    if (modes) {
        for (int i = 0; i < count; i++) {
            if (i == 0 || (modes[i]->w != modes[i-1]->w)) {
                availableModes.push_back({
                    modes[i]->w, 
                    modes[i]->h, 
                    std::to_string(modes[i]->w) + "x" + std::to_string(modes[i]->h)
                });
            }
        }

        SDL_free(modes);
    }
}

void GameSettingsMenu::applySettings(SDL_Window* window, SDL_Renderer* renderer) {
    ResMode target = availableModes[selectedIdx];
    SDL_SetWindowSize(window, target.w, target.h);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetRenderLogicalPresentation(renderer, target.w, target.h, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    
    #ifdef DEBUG
    std::cout << "Applied resolution: " << target.label.c_str() << std::endl; 
    #endif
}

void GameSettingsMenu::nextResolution() {
    selectedIdx = (selectedIdx + 1) % availableModes.size();
}