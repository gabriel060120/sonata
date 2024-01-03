#pragma once
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;

class Scene {
    private:
        RenderWindow* window;
        Texture floorTexture;
        RectangleShape floorRectangle;
        Vector2f floorSize;
    public:
        Scene(RenderWindow* window);
        void renderFloor();
};