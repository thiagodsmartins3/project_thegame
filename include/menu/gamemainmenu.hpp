#ifndef GAMEMAINMENU_HPP
#define GAMEMAINMENU_HPP

#include <iostream>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class GameMainMenu {
    public:
        enum class AppState {
            MainMenu, 
            Playing, 
            Quitting
        };

        struct Button {
            SDL_FRect rect;
            SDL_Color color;
            std::string text;
            SDL_Texture* labelTexture;
        };

    public:
        GameMainMenu(SDL_Renderer* renderer, TTF_Font* font);
        void eventHandler(SDL_Event* event);
        void draw(SDL_Renderer* renderer);
        AppState status() const; 
        void status(AppState appState);

    private:
        AppState currentStatus;
        std::vector<Button> buttons;
        //TTF_Font* font;
};

#endif