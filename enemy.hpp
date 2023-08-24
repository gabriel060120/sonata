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

        float frame;
        float gameTime;
        float movimentSpeed;
        float dx, dy;
        int attackDistance;

        bool onGround;
        bool inMoviment;
        bool inJump;
        bool inFall;


        int groundPosition;
        FloatRect rect;
    public:
        // Sprite sprite;
        RectangleShape sprite;

        Enemy(RenderWindow* renderWindow, int groundLocalization, Player * player);

        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock);
        void update();
        void block();
        void moviment();
        void idle();
        void render();
};