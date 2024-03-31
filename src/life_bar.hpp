#pragma once
#define LIFE_BAR_HPP
#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;

class LifeBar {
    private:
        Vector2f size;
        int life;
        int max;
        Vector2f position;
        RenderWindow* window;
        Color remainderLifeColor; 
        Color lostLifeColor;
    public:

        LifeBar(RenderWindow* renderWindow, Vector2f size, int max, Vector2f position, Color remainderLifeColor, Color lostLifeColor);

        void refresh();
        void setPosition(sf::Vector2f position);
        // void updateGameTime(float clock, bool allowedAction);
        // void update(float clock, bool allowedAction);
        
        //actions
        void takeDamage(int valueDamage);

        //getters
        int getLife();

        //render object
        void render();
};