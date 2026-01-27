#include "../../include/actor/actorcharacter.hpp"

ActorCharacter::ActorCharacter(int characterSpeed) {
    speed = characterSpeed;
}

void ActorCharacter::Tick(float deltaTime) {
    float posX = this->GetPosition().x;
    float posY = this->GetPosition().y;

    const bool* Keys = SDL_GetKeyboardState(NULL);
    if (Keys[SDL_SCANCODE_W]) {
        posY -= speed * deltaTime; 
        this->SetPositionY(posY);
    }
    if (Keys[SDL_SCANCODE_S]) {
        posY += speed * deltaTime; 
        this->SetPositionY(posY);
    }
    if (Keys[SDL_SCANCODE_A]) {
        posX -= speed * deltaTime;
        this->SetPositionX(posX);
    }
    if (Keys[SDL_SCANCODE_D]) {
        posX += speed * deltaTime;
        this->SetPositionX(posX);
    }
}

void ActorCharacter::Render(SDL_Renderer* renderer, SDL_FRect cameraView) {
    SDL_FRect screenPos = { 
        SDL_roundf(this->GetPosition().x - cameraView.x), 
        SDL_roundf(this->GetPosition().y - cameraView.y), 
        this->GetPosition().w, 
        this->GetPosition().h 
    };

    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    SDL_RenderFillRect(renderer, &screenPos);
    //SDL_RenderTexture(renderer, Texture, nullptr, sScreenPos);
}