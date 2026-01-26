#include "../../include/actor/combatcomponent.hpp"

CombatComponent::CombatComponent(Actor* actor, int attack) : ActorComponent(actor) {
    attackPower = attack;
}

void CombatComponent::attack(HealthComponent& health) {
    if (!health.isAlive()) {
        return;
    }

    health.takeDamage(attackPower);
}