#include "../../include/fps/gamefps.hpp"
#include <iostream>

GameFps::GameFps() {
    texture = nullptr;
    rect = { 0, 0, 0, 0 };
    updateTimer = 0.0f;
    lastFps = -1;
}

GameFps::~GameFps() {
    if (texture) {
        SDL_DestroyTexture(texture);
    } 
}

void GameFps::update(float dt, int currentFps, TTF_Font* font, SDL_Renderer* renderer) {
    updateTimer += dt;
    if (updateTimer >= 0.5f && currentFps != lastFps) {
        lastFps = currentFps;
        updateTimer = 0.0f;

        if (texture) SDL_DestroyTexture(texture);

        std::string text = "FPS: " + std::to_string(currentFps);
        SDL_Color white = { 0, 0, 0 };

        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, white);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        
        if (surface) {
            rect.w = (float)surface->w;
            rect.h = (float)surface->h;
            rect.x = 10.0f;
            rect.y = 10.0f;

            SDL_DestroySurface(surface);
        }
    }
}

void GameFps::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderTexture(renderer, texture, NULL, &rect);
    }
}