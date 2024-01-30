#pragma once
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <memory>
using namespace sf;

class Scene {
    private:
        RenderWindow* window;
        //floor
        Texture floorTexture;
        RectangleShape floorRectangle;
        Vector2f floorSize;
        // background
        Texture backgroundTexture;
        RectangleShape backgroundRectangle;
        Vector2f backgroundSize;

    public:
        Scene(RenderWindow* window);
        void render();
        void renderFloor();
        void renderBackground();
};