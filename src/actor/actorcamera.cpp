#include <SDL3/SDL_stdinc.h>
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

    viewRect.x = FMath::Lerp(viewRect.x, targetX, 12.0f * deltaTime);
    viewRect.y = FMath::Lerp(viewRect.y, targetY, 12.0f * deltaTime);
}

void ActorCamera::Clamp(SDL_FRect bounds) {
    viewRect.x = SDL_clamp(viewRect.x, bounds.x, bounds.w - viewRect.w);
    viewRect.y = SDL_clamp(viewRect.y, bounds.y, bounds.h - viewRect.h);

    if (SDL_fabsf(viewRect.x - bounds.x) < 1.0f) viewRect.x = bounds.x;
    if (SDL_fabsf(viewRect.y - bounds.y) < 1.0f) viewRect.y = bounds.y;

    viewRect.x = SDL_floorf(viewRect.x);
    viewRect.y = SDL_floorf(viewRect.y);
}

void ActorCamera::Target(Actor* target) {
    actorTarget = target;
}

SDL_FRect ActorCamera::CameraView() const {
    return viewRect;
}