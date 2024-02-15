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
    
    public:
        FinishPage(sf::RenderWindow* window, bool isWon);
        void render();
        bool verifyInput();
};