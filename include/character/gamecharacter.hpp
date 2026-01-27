#ifndef GAMECHARACTER_HPP
#define GAMECHARACTER_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class GameCharacter {
    public:
        GameCharacter(SDL_Renderer* renderer);
        ~GameCharacter();
        void update(float dt, float vx, float vy);
        void draw(SDL_Renderer* renderer, SDL_FRect camera);
        float getWorldPosX() const;
        void setWorldPosX(int posX);
        float getWorldPosY() const;
        void setWorldPosY(int posY);

    private:
        SDL_FRect worldPos;
        SDL_Texture* texture;
        int currentFrame;
        int direction;
        float animTimer;
};

#endif