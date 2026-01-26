#include "../../include/actor/healthcomponent.hpp"

HealthComponent::HealthComponent(Actor* actor, int actorHealth) : ActorComponent(actor) {
    maxHealth = actorHealth;
    health = actorHealth;
}

void HealthComponent::takeDamage(int damage) {
    health = std::max(0, health - damage);

    if (health == 0 && onDeath) {
        onDeath();
    }
}

void HealthComponent::heal(int amount) {
    health = std::min(maxHealth, health + amount);
}

int HealthComponent::getHealth() const {
    return health;
}

bool HealthComponent::isAlive() const {
    return health > 0;
}