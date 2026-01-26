#include "../../include/actor/actor.hpp"

Actor::Actor() {

}

void Actor::SetPosition(float posX, float posY) {
    actor = { 0.0f, 0.0f, 64.0f, 64.0f };
    isActive = true;
}

SDL_FRect Actor::GetPosition() const {

}

SDL_Point Actor::GetCenterPosition() const {

}