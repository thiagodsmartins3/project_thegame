#ifndef ACTORCHARACTER_HPP
#define ACTORCHARACTER_HPP

#include <SDL3/SDL.h>
#include "actor.hpp"

class ActorCharacter: public Actor {
    public:
        ActorCharacter(SDL_Texture* texture, int characterSpeed = 300);
        void Tick(float deltaTime) override;
        void Render(SDL_Renderer* renderer, SDL_FRect cameraView);

    private:
        int speed;
        SDL_Texture* characterTexture;
        SDL_FlipMode flip;
        int totalFrames;      
        int currentFrame;
        float animTimer;
        float frameDuration;
        int frameWidth;      
        int frameHeight;
};

#endif