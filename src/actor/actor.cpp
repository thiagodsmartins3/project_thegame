#include "../../include/actor/actor.hpp"

Actor::Actor() {
    actor = { 0.0f, 0.0f, 64.0f, 64.0f };
    isActive = true;
}

void Actor::SetPosition(SDL_FRect worldPosition) {
    actor = worldPosition;
}

void Actor::SetPosition(float posX, float posY) {
    actor.x = posX;
    actor.y = posY;
}

void Actor::SetPositionX(float pos) {
    actor.x = pos;
}

void Actor::SetPositionY(float pos) {
    actor.y = pos;
}

SDL_FRect Actor::GetPosition() const {
    return actor;
}

SDL_FPoint Actor::GetCenterPosition() const {
    return {
        actor.x + (actor.w / 2.0f),
        actor.y + (actor.h / 2.0f)
    };
}

void Actor::Tick(float deltaTime) {

}

Actor::~Actor() { 
    
}