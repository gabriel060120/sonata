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

        float frame;
        float gameTime;
        float movimentSpeed;
        float dx, dy;
        float timerActionTransition;
        float actiontransitionTime;
        //action
        int actionIndex;
        RectangleShape attackBox;
        bool attackingAction;
        bool blockingAction;

        int groundPosition;
        FloatRect rect;

        std::unique_ptr<LifeBar> lifeBar; 

    public:
        // Sprite sprite;
        RectangleShape sprite;

        Player(RenderWindow* renderWindow, int groundLocalization);

        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock);
        void update(float clock);
        //actions
        void actions();
        void block();
        void attack();
        void moviment();
        void idle();
        //getters
        RectangleShape getAttackBox();
        bool inAttacking();
        bool inBlocking();
        //reactions
        void takeDamage(int valueDamage);

        void render();
};