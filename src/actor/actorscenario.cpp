#include "../../include/actor/actorscenario.hpp"

ActorScenario::ActorScenario(float width, float height) {
    scenarioBounds = {0.0f, 0.0f, width, height};
}

void ActorScenario::Render(SDL_Renderer* renderer, SDL_FRect cameraView) {
    SDL_FRect screenRect = { -cameraView.x, -cameraView.y, scenarioBounds.w, scenarioBounds.h };
    SDL_SetRenderDrawColor(renderer, 40, 40, 45, 255);
    SDL_RenderFillRect(renderer, &screenRect);
        
    SDL_SetRenderDrawColor(renderer, 60, 60, 70, 255);  
    for(int i = 0; i < scenarioBounds.w; i += 200) {
        SDL_RenderLine(renderer, i - cameraView.x, -cameraView.y, i - cameraView.x, scenarioBounds.h - cameraView.y);
    }
}

SDL_FRect ActorScenario::ScenarioBounds() const {
    return scenarioBounds;
}

void ActorScenario::Constraint(Actor* actor) {
    if (!actor) return;

    SDL_FRect pos = actor->GetPosition();

    pos.x = SDL_clamp(pos.x, scenarioBounds.x, scenarioBounds.w - pos.w);
    pos.y = SDL_clamp(pos.y, scenarioBounds.y, scenarioBounds.h - pos.h);

    actor->SetPosition(pos.x, pos.y);
}