#include "../../include/actor/actorcamera.hpp"

struct FMath {
    static float Lerp(float A, float B, float Alpha) {
        return A + Alpha * (B - A);
    }
};

ActorCamera::ActorCamera(float width, float height) {
    viewRect = { 0.0f, 0.0f, width, height };
    actorTarget = nullptr;
}

void ActorCamera::Tick(float deltaTime) {
    if (!actorTarget) return;

    float targetX = (actorTarget->GetPosition().x + actorTarget->GetPosition().w / 2) - (viewRect.w / 2);
    float targetY = (actorTarget->GetPosition().y + actorTarget->GetPosition().h / 2) - (viewRect.h / 2);

    viewRect.x = FMath::Lerp(viewRect.x, targetX, 5.0f * deltaTime);
    viewRect.y = FMath::Lerp(viewRect.y, targetY, 5.0f * deltaTime);
}

void ActorCamera::Clamp(SDL_FRect bounds) {
    viewRect.x = SDL_clamp(viewRect.x, 0, bounds.w - viewRect.w);
    viewRect.y = SDL_clamp(viewRect.y, 0, bounds.h - viewRect.h);
}