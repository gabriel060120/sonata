#pragma once
#define ENGINE_H
#include <SFML/Graphics.hpp>

class FinishPage {
    private:
        bool isWon;
        sf::RenderWindow* window;
        sf::Font font;
        sf::Text title;
        sf::Text description;
        bool isRendering;
    
    public:
        FinishPage(sf::RenderWindow* window);
        void init(bool isWon);
        void render();
        bool verifyInput();
};