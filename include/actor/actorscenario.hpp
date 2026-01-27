#ifndef ACTORSCENARIO_HPP
#define ACTORSCENARIO_HPP

#include <SDL3/SDL.h>
#include "actor.hpp"

class ActorScenario: public Actor {
    public:
        ActorScenario(SDL_Texture* texture, float width, float height);
        void Render(SDL_Renderer* renderer, SDL_FRect cameraView);
        void Constraint(Actor* actor);
        SDL_FRect ScenarioBounds() const;

    private:
        SDL_FRect scenarioBounds;
        float parallaxEffect;
        SDL_Texture* backgroundTexture;
};

#endif