#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include <functional>
#include <algorithm>
#include "actorcomponent.hpp"

class HealthComponent: public ActorComponent {
    public:
        HealthComponent(Actor* actor, int actorHealth);
        void takeDamage(int damage);
        void heal(int amount);
        int getHealth() const;
        bool isAlive() const;
        std::function<void()> onDeath;

    private:
        int maxHealth;
        int health;
};

#endif