#pragma once
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "player.hpp"
using namespace sf;

class Enemy{
    private:
        RenderWindow* window;
        Texture texture;
        Player * player;

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
        bool changeAction;
        bool inMoviment;
        bool inPreparingAttack;
        bool inAttacking;
        bool inTakingDamage;

        int groundPosition;
        FloatRect rect;
    public:
        // Sprite sprite;
        RectangleShape sprite;

        Enemy(RenderWindow* renderWindow, int groundLocalization, Player * player);

        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock);
        void update(float clock);
        
        //actions
        void idle();
        void moviment();
        void preparingAttack();
        void attack();

        //render object
        void render();
};