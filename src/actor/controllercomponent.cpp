#include <SDL3/SDL.h>
#include "../../include/actor/controllercomponent.hpp"

ControllerComponent::ControllerComponent(Actor* actor) : ActorComponent(actor) {
    posX = 0.0f;
    posY = 0.0f;
}

void ControllerComponent::move() {
    const bool* keys = const_cast<bool*>(SDL_GetKeyboardState(nullptr));
    posX = 0;
    posY = 0;

    if (keys[SDL_SCANCODE_A]) posX = -1;
    if (keys[SDL_SCANCODE_D]) posX = 1;
    if (keys[SDL_SCANCODE_W]) posY = -1;
    if (keys[SDL_SCANCODE_S]) posY = 1;
}

float ControllerComponent::getPosX() const {
    return posX;
}

float ControllerComponent::getPosY() const {
    return posY;
}