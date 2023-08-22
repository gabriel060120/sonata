#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "player.hpp"

using namespace std;
using namespace sf;

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720),"Plataforma 2D", sf:: Style::Titlebar | sf::Style::Close);
    window->setPosition(Vector2i(80,0));
    // window->setFramerateLimit(60);

    const float heightFloor = 100.f;
    float timeClock = 0.f;
    Clock gameClock;

    int groundLocalization = window->getSize().y - heightFloor;

    Player player(window.get(), groundLocalization);

    // Texture backgroundTexture;
    // backgroundTexture.loadFromFile("./assets/img/bg.jpg");
    // Sprite backgroundSprite(backgroundTexture);

    // Texture floorTexture;
    RectangleShape floor(Vector2f(window->getSize().x, heightFloor));
    // floorTexture.loadFromFile("./assets/img/floormax.jpg");
    // Sprite floorSprite(floorTexture);
    floor.setPosition(0.f, window->getSize().y - heightFloor);
    
    while(window->isOpen())
    {
        timeClock = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
        player.updateGameTime(timeClock);

        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        
        player.action();

        window->clear();
        // window->draw(backgroundSprite);
        window->draw(floor);
        player.render();
        window->display();
    }

        
    return EXIT_SUCCESS;
}