#include "../../include/actor/actorscenario.hpp"

ActorScenario::ActorScenario(SDL_Texture* texture, float width, float height) {
    scenarioBounds = {0.0f, 0.0f, width, height};
    parallaxEffect = 0.5f;
    backgroundTexture = texture;
}

void ActorScenario::Render(SDL_Renderer* renderer, SDL_FRect cameraView) {
    SDL_FRect screenRect = { 
        -cameraView.x, 
        -cameraView.y, 
        scenarioBounds.w, 
        scenarioBounds.h 
    };

    SDL_SetRenderDrawColor(renderer, 40, 40, 45, 255);
    SDL_RenderFillRect(renderer, &screenRect);

    SDL_FRect screenPos = {
        SDL_floorf(0.0f - (cameraView.x * parallaxEffect)),
        SDL_floorf(0.0f - (cameraView.y * parallaxEffect)),
        scenarioBounds.w,
        scenarioBounds.h
    };

    SDL_RenderTexture(renderer, backgroundTexture, nullptr, &screenPos);
}

SDL_FRect ActorScenario::ScenarioBounds() const {
    return scenarioBounds;
}

void ActorScenario::Constraint(Actor* actor) {
    if (!actor) return;

    SDL_FRect pos = actor->GetPosition();

    pos.x = SDL_clamp(
        pos.x, 
        scenarioBounds.x, 
        scenarioBounds.w - pos.w
    );

    pos.y = SDL_clamp(
        pos.y, 
        scenarioBounds.y, 
        scenarioBounds.h - pos.h
    );

    actor->SetPosition(pos.x, pos.y);
}