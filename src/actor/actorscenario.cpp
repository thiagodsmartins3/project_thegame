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