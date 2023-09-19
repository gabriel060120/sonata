#pragma once
#define PLAYER_H
#include<SFML/Graphics.hpp>
#include <memory>
#include "life_bar.hpp"

using namespace sf;

class Player {
    private:
        RenderWindow* window;
        Texture texture;
        //game
        float frame;
        float gameTime;
        bool triggerAction;
        //action        
        float movimentSpeed;
        float dx, dy;
        float timerActionTransition;
        float actiontransitionTime;
        int actionIndex;
        bool hitTrigger;
        RectangleShape attackBox;
        bool attackingAction;
        bool blockingAction;
        bool longSleepingAction;
        bool shortSleepingAction;

        int groundPosition;
        FloatRect rect;

        std::unique_ptr<LifeBar> lifeBar; 

    public:
        // Sprite sprite;
        RectangleShape sprite;

        Player(RenderWindow* renderWindow, int groundLocalization);

        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock, bool triggerAction);
        void update(float clock, bool triggerAction);
        //actions
        void actions();
        void block();
        void attack();
        void moviment();
        void idle();
        void longSleep();
        void shortSleep();
        //getters
        RectangleShape getAttackBox();
        bool inAttacking();
        bool inBlocking();
        //reactions
        void takeDamage(int valueDamage);

        void render();
};