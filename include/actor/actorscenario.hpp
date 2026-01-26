#ifndef ACTORSCENARIO_HPP
#define ACTORSCENARIO_HPP

#include <SDL3/SDL.h>
#include "actor.hpp"

class ActorScenario: public Actor {
    public:
        ActorScenario(float width, float height);
        void Render(SDL_Renderer* renderer, SDL_FRect cameraView);

    private:
        SDL_FRect scenarioBounds;
};

#endif