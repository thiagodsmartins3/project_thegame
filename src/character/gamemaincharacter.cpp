#include "../../include/character/gamemaincharacter.hpp"

GameMainCharacter::GameMainCharacter(int maxHealth, int attackPower, SDL_Renderer* renderer) {
    characterHealth = std::make_unique<HealthComponent>(this, maxHealth);
    characterCombat = std::make_unique<CombatComponent>(this, attackPower);
    characterDraw = std::make_unique<DrawComponent>(this, renderer);

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

void GameMainCharacter::update(float dt, SDL_FRect bounds) {
    characterDraw->update(dt, characterController->getPosX(), characterController->getPosY(), bounds);
}

void GameMainCharacter::cameraPosition(SDL_FRect* camera) {

}

void GameMainCharacter::move() {
    characterController->move();
}