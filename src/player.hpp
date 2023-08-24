#pragma once
#define PLAYER_H
#include<SFML/Graphics.hpp>
#include <memory>

using namespace sf;

class Player {
    private:
        RenderWindow* window;
        Texture texture;

        float frame;
        float gameTime;
        float movimentSpeed;
        float dx, dy;

        bool onGround;
        bool inMoviment;
        bool inJump;
        bool inFall;


        int groundPosition;
        FloatRect rect;
        

    public:
        // Sprite sprite;
        RectangleShape sprite;

        Player(RenderWindow* renderWindow, int groundLocalization);

        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock);
        void update();
        void block();
        void moviment();
        void idle();
        void render();
};