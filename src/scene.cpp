#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Scene::Scene(RenderWindow* window) {
    this->window = window;
    
    //floor
    floorTexture.loadFromFile("./../assets/ground/ground.png");
    floorSize = Vector2f(floorTexture.getSize().x, floorTexture.getSize().y);
    floorRectangle.setSize(floorSize);
    floorRectangle.setTexture(&floorTexture);
    
    //background
    backgroundTexture.loadFromFile("./../assets/background/background.png");
    backgroundSize = Vector2f(backgroundTexture.getSize().x/2, backgroundTexture.getSize().y/2);
    backgroundRectangle.setSize(backgroundSize);
    backgroundRectangle.setTexture(&backgroundTexture);
    backgroundRectangle.setTextureRect(IntRect(Vector2i(0,0),Vector2i(backgroundTexture.getSize().x/2, backgroundTexture.getSize().y/2)));
}

void Scene::renderBackground() {
    float positionY = 0.f;
    float positionX = 0.f;
    int maxLine = (window->getSize().y / backgroundRectangle.getSize().y) + 1;
    int maxcolumn = (window->getSize().x / backgroundRectangle.getSize().x) + 1;
    for(int line = 0; line < maxLine; line++) {
        for(int column = 0; column < maxcolumn; column++) {
            backgroundRectangle.setPosition(Vector2f(positionX, positionY));
            window->draw(backgroundRectangle);
            positionX += backgroundRectangle.getSize().x;
        }
        positionY += backgroundRectangle.getSize().y;
        positionX = 0.f;
    }    
}

void Scene::renderFloor() {
    float floorPositionY = window->getSize().y - floorTexture.getSize().y;
    float floorPositionX = 0.f;
    int repeat = (window->getSize().x / floorTexture.getSize().x) + 1;

    for(int count = 0; count < repeat; count++) {
        floorRectangle.setPosition(Vector2f(floorPositionX, floorPositionY));
        window->draw(floorRectangle);
        floorPositionX += floorTexture.getSize().x;
    }
}

void Scene::render() {
    renderBackground();
    renderFloor();
}