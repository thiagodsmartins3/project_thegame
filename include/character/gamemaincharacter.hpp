#ifndef GAMEMAINCHARACTER_HPP
#define GAMEMAINCHARACTER_HPP

#include <iostream>
#include <memory>
#include "../actor/actor.hpp"
#include "../actor/combatcomponent.hpp"
#include "../actor/healthcomponent.hpp"
#include "../actor/drawcomponent.hpp"
#include "../actor/controllercomponent.hpp"

class GameMainCharacter: public Actor {
    public:
        GameMainCharacter(int maxHealth, int attackPower, SDL_Renderer* renderer);
        void attack(GameMainCharacter& target);
        HealthComponent& getHealth() const;
        void update(float dt, SDL_FRect bounds);
        void cameraPosition(SDL_FRect* camera);
        void move();

    private:
        std::unique_ptr<HealthComponent> characterHealth;
        std::unique_ptr<CombatComponent> characterCombat;
        std::unique_ptr<DrawComponent> characterDraw;
        std::unique_ptr<ControllerComponent> characterController;
};

#endif
