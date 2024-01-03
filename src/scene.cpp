#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Scene::Scene(RenderWindow* window) {
    this->window = window;
    floorTexture.loadFromFile("./../assets/ground/ground.png");
    floorSize = Vector2f(floorTexture.getSize().x, floorTexture.getSize().y);
    floorRectangle.setSize(floorSize);
    floorRectangle.setTexture(&floorTexture);
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