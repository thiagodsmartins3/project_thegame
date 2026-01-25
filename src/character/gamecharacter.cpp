#include "../../include/character/gamecharacter.hpp"
#include "../../utility/paths.hpp"

GameCharacter::GameCharacter(SDL_Renderer* renderer) {
    texture = IMG_LoadTexture(renderer, Paths::getInstance().IMAGES("samurai.png").c_str());
    worldPos = { 100.0f, 100.0f, 64.0f, 64.0f }; // Size of 1 sprite frame
}

GameCharacter::~GameCharacter() {

}

void GameCharacter::update(float dt, float vx, float vy) {
    // Update Position
    worldPos.x += vx * 300.0f * dt;
    worldPos.y += vy * 300.0f * dt;

    // Determine Direction Row
    if (vy > 0) direction = 0;
    else if (vx < 0) direction = 1;
    else if (vx > 0) direction = 2;
    else if (vy < 0) direction = 3;

        // Animate if moving
    if (vx != 0 || vy != 0) {
        animTimer += dt;
            if (animTimer > 0.15f) {
                animTimer = 0;
                currentFrame = (currentFrame + 1) % 4;
            }
    } else {
        currentFrame = 0;
    }
}

void GameCharacter::draw(SDL_Renderer* renderer, SDL_FRect camera) {
    SDL_FRect srcRect = { (float)currentFrame * 64, (float)direction * 64, 64, 64 };
    SDL_FRect dstRect = { worldPos.x - camera.x, worldPos.y - camera.y, 64, 64 };
    SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
}

float GameCharacter::getWorldPosX() const {
    return worldPos.x;
}

void GameCharacter::setWorldPosX(int posX) {
    worldPos.x = posX;
}

float GameCharacter::getWorldPosY() const {
    return worldPos.y;
}

void GameCharacter::setWorldPosY(int posY) {
    worldPos.y = posY;
}