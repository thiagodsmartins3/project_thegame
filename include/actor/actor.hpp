#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SDL3/SDL.h>

class Actor {
    public:
        Actor();
        void SetPosition(float posX, float posY);
        SDL_FRect GetPosition() const;
        SDL_Point GetCenterPosition() const;
        virtual ~Actor();

    private:
        SDL_FRect actor;
        bool isActive;
};

#endif