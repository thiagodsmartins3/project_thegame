#ifndef CAMERAACTOR_HPP
#define CAMERAACTOR_HPP

#include <SDL3/SDL.h>
#include "actor.hpp"

class CameraActor: public Actor {
    public:
        CameraActor(SDL_FRect view);
        void setTarget(Actor* targetActor);
        SDL_FRect cameraPostion() const;
        void updatePosition();

    private:
        Actor* actor;
        SDL_FRect viewRect;
        SDL_FRect outOfBoundsZone;
};


#endif