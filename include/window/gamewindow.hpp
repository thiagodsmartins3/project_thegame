#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <string>
#include "../../utility/sdldeleters.hpp"
#include "../fps/gamefps.hpp"

class GameWindow {
    public:
        struct GameWindowInfo {
            std::string title;
            int width;
            int height;
        };

    public:
        GameWindow();
        GameWindow(const GameWindowInfo& windowInfo);
        ~GameWindow();
        void run();
        void getAvaliableDisplayResolutions();

    private:
        void setupWindow();

    private:
        std::unique_ptr<SDL_Window, SDLWindowDeleter> window;
        std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> windowSurface;
        std::shared_ptr<SDL_Renderer> renderer;
        SDL_Event event;
        GameWindowInfo gameWindowInfo;
        bool isRunning;
        GameFps fps;
        TTF_Font* font;
};

#endif