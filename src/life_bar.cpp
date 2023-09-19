#include "life_bar.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;


LifeBar::LifeBar(RenderWindow* renderWindow, Vector2f size, int max, Vector2f position, Color remainderLifeColor, Color lostLifeColor) {
    this->size = size;
    this->max = max;
    this->life = max;
    this->position = position;
    this->window = renderWindow;
    this->remainderLifeColor = remainderLifeColor; 
    this->lostLifeColor = lostLifeColor;    
}

void LifeBar::setPosition(Vector2f position) {
    this->position = position;
}

void LifeBar::takeDamage(int valueDamage) {
    life -= valueDamage;
    if(life < 0) {
        life = 0;
    }
}

int LifeBar::getLife() {
    return life;
}

void LifeBar::render() {
    for(int i = 0; i < max; i++) {
        RectangleShape itemBar(size); 
        float positionX = position.x + (itemBar.getGlobalBounds().width * i);
        itemBar.setPosition(positionX, position.y);
        
        if(i < life) {
            itemBar.setFillColor(remainderLifeColor);
        } else {
            itemBar.setFillColor(lostLifeColor);
        }

        window->draw(itemBar);
    }
}