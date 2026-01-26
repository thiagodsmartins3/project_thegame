#include "../../include/actor/cameraactor.hpp"

CameraActor::CameraActor(SDL_FRect view) {
    viewRect = view;
}

void CameraActor::setTarget(Actor* targetActor) {
    actor = targetActor;
}

SDL_FRect CameraActor::cameraPostion() const {
    return viewRect;
}

void CameraActor::updatePosition() {
    // viewRect.x = player.getWorldPosX() - (viewRect.w / 2) + 32;
    // viewRect.y = player.getWorldPosY() - (viewRect.h / 2) + 32;
    // viewRect.x = SDL_clamp(viewRect.x, 0, worldBounds.w - viewRect.w);
    // viewRect.y = SDL_clamp(viewRect.y, 0, worldBounds.h - viewRect.h);
}