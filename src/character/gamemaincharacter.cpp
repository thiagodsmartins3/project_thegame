#include "../../include/character/gamemaincharacter.hpp"

GameMainCharacter::GameMainCharacter(int maxHealth, int attackPower) {
    characterHealth = std::make_unique<HealthComponent>(this, maxHealth);
    characterCombat = std::make_unique<CombatComponent>(this, attackPower);

    characterHealth->onDeath = [this]() {
        std::cout << "You're dead" << std::endl;
    };
}

void GameMainCharacter::attack(GameMainCharacter& target) {
    characterCombat->attack(*target.characterHealth);
}

HealthComponent& GameMainCharacter::getHealth() const {
    return *characterHealth;
}