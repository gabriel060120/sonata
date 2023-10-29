#pragma once
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "life_bar.hpp"
using namespace sf;

class Enemy{
    private:
        RenderWindow* window;
        Texture texture;
        Player * player;
        std::unique_ptr<LifeBar> lifeBar;

        //game timers
        float frame;
        float gameClock;

        //moviment
        float movimentSpeed;
        float dx, dy;
        int attackDistance;

        //action timers
        float timePreparingAttack;
        float timeAttack;
        float timerAction;

        // actions control
        bool allowedAction;
        bool changeAction;
        bool inIdle;
        bool inMoviment;
        bool inPreparingAttack;
        bool inAttacking;
        bool inTakingDamage;
        bool toIdle;
        bool toPreparingAttack;
        bool toAttack;
        bool toTakingDamage;
        bool stateChanged;
        int state;

        int groundPosition;
        FloatRect rect;
    public:
        // Sprite sprite;
        RectangleShape sprite;

        Enemy(RenderWindow* renderWindow, int groundLocalization, Player * player);

        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock, bool allowedAction);
        void update(float clock, bool allowedAction);
        
        //actions
        void idle();
        void moviment();
        void preparingAttack();
        void attack();
        //reactions
        void takeDamage();
        //getters
        int getLife();
        int getState();
        //render object
        void render();
};