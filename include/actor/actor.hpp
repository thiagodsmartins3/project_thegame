#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SDL3/SDL.h>

class Actor {
    public:
        Actor();
        void SetPosition(SDL_FRect worldPosition);
        void SetPosition(float posX, float posY);
        void SetPositionX(float pos);
        void SetPositionY(float pos);
        void IsActive(bool active);
        bool IsActive() const;
        SDL_FRect GetPosition() const;
        SDL_FPoint GetCenterPosition() const;
        virtual void Tick(float deltaTime);
        virtual ~Actor();

    private:
        SDL_FRect actor;
        bool isActive;
};

#endif