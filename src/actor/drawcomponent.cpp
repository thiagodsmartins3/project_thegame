#include <string>
#include "../../include/actor/drawcomponent.hpp"
#include "../../utility/paths.hpp"

DrawComponent::DrawComponent(Actor* actor, SDL_Renderer* renderer) : ActorComponent(actor) {
    texture = IMG_LoadTexture(renderer, Paths::getInstance().IMAGES("samurai.png").c_str());
    worldPos = { 100.0f, 100.0f, 64.0f, 64.0f };
}

void DrawComponent::update(float dt, float vx, float vy, SDL_FRect bounds) {
    worldPos.x += vx * 300.0f * dt;
    worldPos.y += vy * 300.0f * dt;

    if (vy > 0) direction = 0;
    else if (vx < 0) direction = 1;
    else if (vx > 0) direction = 2;
    else if (vy < 0) direction = 3;

    if (vx != 0 || vy != 0) {
        animTimer += dt;
            if (animTimer > 0.15f) {
                animTimer = 0;
                currentFrame = (currentFrame + 1) % 4;
            }
    } else {
        currentFrame = 0;
    }

    checkBounds(bounds);
}

void DrawComponent::draw(SDL_Renderer* renderer, SDL_FRect camera) {
    SDL_FRect srcRect = { (float)currentFrame * 64, (float)direction * 64, 64, 64 };
    SDL_FRect dstRect = { worldPos.x - camera.x, worldPos.y - camera.y, 64, 64 };
    SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
}

void DrawComponent::checkBounds(SDL_FRect bounds) {
    if (worldPos.x < 0) worldPos.x = 0;
    if (worldPos.y < 0) worldPos.y = 0;
    if (worldPos.x >  bounds.w - 64) worldPos.x = bounds.w - 64;
    if (worldPos.y > bounds.h - 64) worldPos.y = bounds.h - 64;
}