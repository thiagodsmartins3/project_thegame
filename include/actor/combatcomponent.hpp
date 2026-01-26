#ifndef COMBATCOMPONENT_HPP
#define COMBATCOMPONENT_HPP

#include "actorcomponent.hpp"
#include "healthcomponent.hpp"

class CombatComponent: public ActorComponent {
    public:
        CombatComponent(Actor* actor, int attack);
        void attack(HealthComponent& health);

    private:
        int attackPower;
};

#endif