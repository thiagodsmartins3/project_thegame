#include "../../include/menu/gamemainmenu.hpp"

GameMainMenu::GameMainMenu(SDL_Renderer* renderer, TTF_Font* font) {
    TTF_Init();

    currentStatus = AppState::MainMenu;

    buttons.push_back({{540, 250, 200, 60}, {50, 50, 200, 255}, "PLAY", nullptr});
    buttons.push_back({{540, 350, 200, 60}, {200, 50, 50, 255}, "QUIT", nullptr});

    SDL_Color white = {255, 255, 255, 255};
    for (auto& btn : buttons) {
        SDL_Surface* surf = TTF_RenderText_Blended(font, btn.text.c_str(), 0, white);
        btn.labelTexture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_DestroySurface(surf);
    }
}

void GameMainMenu::eventHandler(SDL_Event* event) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float mouseX = event->button.x;
        float mouseY = event->button.y;

        for (size_t i = 0; i < buttons.size(); ++i) {
            if (mouseX >= buttons[i].rect.x && mouseX <= buttons[i].rect.x + buttons[i].rect.w &&
                mouseY >= buttons[i].rect.y && mouseY <= buttons[i].rect.y + buttons[i].rect.h) {    
                    if (i == 0) currentStatus = AppState::Playing;
                    if (i == 1) currentStatus = AppState::Quitting;
            }
        }
    }
}

void GameMainMenu::draw(SDL_Renderer* renderer) {
    for (const auto& btn : buttons) {
        SDL_SetRenderDrawColor(renderer, btn.color.r, btn.color.g, btn.color.b, 255);
        SDL_RenderFillRect(renderer, &btn.rect);

        float textW, textH;
        SDL_GetTextureSize(btn.labelTexture, &textW, &textH);
        SDL_FRect textRect = { 
            btn.rect.x + (btn.rect.w - textW) / 2.0f, 
            btn.rect.y + (btn.rect.h - textH) / 2.0f, 
            textW, textH 
        };
        SDL_RenderTexture(renderer, btn.labelTexture, NULL, &textRect);
    }
}

GameMainMenu::AppState GameMainMenu::status() const {
    return currentStatus;
} 

void GameMainMenu::status(GameMainMenu::AppState appState) {
    currentStatus = appState;
}