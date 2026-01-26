#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#include "actor.hpp"
#include "actorcomponent.hpp"

class ControllerComponent: public ActorComponent {
    public:
        ControllerComponent(Actor* actor);
        void move();
        float getPosX() const;
        float getPosY() const;
        
    private:
        float posX;
        float posY;
};

#endif