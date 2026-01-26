#ifndef DRAWCOMPONENT_HPP
#define DRAWCOMPONENT_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "actor.hpp"
#include "actorcomponent.hpp"

class DrawComponent: public ActorComponent {
    public:
        DrawComponent(Actor* actor, SDL_Renderer* renderer);
        void update(float dt, float vx, float vy, SDL_FRect bounds);
        void draw(SDL_Renderer* renderer, SDL_FRect camera);
        
    private:
        void checkBounds(SDL_FRect scenarioBounds);

    private:
        SDL_FRect worldPos;
        SDL_Texture* texture;
        int currentFrame;
        int direction;
        float animTimer;  
};

#endif