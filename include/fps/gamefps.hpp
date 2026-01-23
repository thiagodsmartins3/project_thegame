#ifndef GAMEFPS_HPP
#define GAMEFPS_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class GameFps {
    public:
        GameFps();
        ~GameFps();
        void update(float dt, int currentFps, TTF_Font* font, SDL_Renderer* renderer);
        void draw(SDL_Renderer* renderer);

    private:
        SDL_Texture* texture;
        SDL_FRect rect;
        float updateTimer;
        int lastFps;
};

#endif