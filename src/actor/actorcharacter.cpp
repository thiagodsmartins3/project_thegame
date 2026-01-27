#include "../../include/actor/actorcharacter.hpp"
#include <iostream>

ActorCharacter::ActorCharacter(SDL_Texture* texture, int characterSpeed) {
    characterTexture = texture;
    flip = SDL_FLIP_NONE;
    speed = characterSpeed;
    totalFrames = 3;  // Remeber: here is set number of frames in the row. I'll change in the future
    currentFrame = 0;
    animTimer = 0.0f;
    frameDuration = 0.1f; // Speed: 0.1s per frame (10 FPS)
    frameWidth = 64;      // Width of one frame in the png
    frameHeight = 64;
}

void ActorCharacter::Tick(float deltaTime) {
    float posX = this->GetPosition().x;
    float posY = this->GetPosition().y;
    this->IsActive(false);

    const bool* Keys = SDL_GetKeyboardState(NULL);

    if (Keys[SDL_SCANCODE_W]) {
        posY -= speed * deltaTime;
        this->IsActive(true); 
        this->SetPositionY(posY);
    }

    if (Keys[SDL_SCANCODE_S]) {
        posY += speed * deltaTime; 
        this->IsActive(true);
        this->SetPositionY(posY);
    }

    if (Keys[SDL_SCANCODE_A]) {
        posX -= speed * deltaTime;
        flip = SDL_FLIP_HORIZONTAL;
        this->IsActive(true);
        this->SetPositionX(posX);
    }

    if (Keys[SDL_SCANCODE_D]) {
        posX += speed * deltaTime;
        flip = SDL_FLIP_NONE;
        this->IsActive(true);
        this->SetPositionX(posX);
    }

    if (this->IsActive()) {
        animTimer += deltaTime;
        if (animTimer >= frameDuration) {
            animTimer = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;
        }
    } else {
        currentFrame = 0;
    }
}

void ActorCharacter::Render(SDL_Renderer* renderer, SDL_FRect cameraView) {
    SDL_FRect sourceRect = {
        (float)(currentFrame * frameWidth),
        0.0f,
        (float)frameWidth,
        (float)frameHeight
    };

    SDL_FRect screenPos = { 
        SDL_roundf(this->GetPosition().x - cameraView.x), 
        SDL_roundf(this->GetPosition().y - cameraView.y), 
        this->GetPosition().w, 
        this->GetPosition().h 
    };

    SDL_RenderTextureRotated(renderer, characterTexture, &sourceRect, &screenPos, 0.0, nullptr, flip);
}