#ifndef ACTORCOMPONENT_HPP
#define ACTORCOMPONENT_HPP

#include "actor.hpp"

class ActorComponent {
    public:
        explicit ActorComponent(Actor* actor) {
            this->actor = actor;
         }
    
    private:
        Actor* actor;
};

#endif