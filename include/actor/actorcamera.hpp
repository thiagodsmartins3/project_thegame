#ifndef ACTORCAMERA_HPP
#define ACTORCAMERA_HPP

#include <SDL3/SDL.h>
#include "actor.hpp"

class ActorCamera: public Actor {
    public:
        ActorCamera(float width, float height);
        void Tick(float deltaTime) override;
        void Clamp(SDL_FRect bounds);

    private:
        SDL_FRect viewRect;
        Actor* actorTarget;
};

#endif