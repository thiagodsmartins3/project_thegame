#ifndef GAMEMAINCHARACTER_HPP
#define GAMEMAINCHARACTER_HPP

#include <iostream>
#include <memory>
#include "../actor/actor.hpp"
#include "../actor/combatcomponent.hpp"
#include "../actor/healthcomponent.hpp"

class GameMainCharacter: public Actor {
    public:
        GameMainCharacter(int maxHealth, int attackPower);
        void attack(GameMainCharacter& target);
        HealthComponent& getHealth() const;

    private:
        std::unique_ptr<HealthComponent> characterHealth;
        std::unique_ptr<CombatComponent> characterCombat;
};

#endif
