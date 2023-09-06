#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "player.hpp"
#include "enemy.hpp"

using namespace std;
using namespace sf;

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720),"Plataforma 2D", sf:: Style::Titlebar | sf::Style::Close);
    window->setPosition(Vector2i(80,0));
    // window->setFramerateLimit(60);

    const float heightFloor = 100.f;
    float timeClock = 0.f;
    float actionInterval = 1.f;
    float timerToAction = 0.f;
    Clock gameClock;
    bool allowedAction = false;

    int groundLocalization = window->getSize().y - heightFloor;

    Player player(window.get(), groundLocalization);
    Enemy enemy(window.get(), groundLocalization, &player);

    // Texture backgroundTexture;
    // backgroundTexture.loadFromFile("./assets/img/bg.jpg");
    // Sprite backgroundSprite(backgroundTexture);

    // Texture floorTexture;
    RectangleShape floor(Vector2f(window->getSize().x, heightFloor));
    floor.setFillColor(Color::Yellow);
    // floorTexture.loadFromFile("./assets/img/floormax.jpg");
    // Sprite floorSprite(floorTexture);
    floor.setPosition(0.f, window->getSize().y - heightFloor);
    
    while(window->isOpen())
    {
        timeClock = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
        timerToAction += timeClock;
        
        if(timerToAction >= actionInterval) {
            allowedAction = true;
            timerToAction = 0.f;
            cout << allowedAction << endl;
        } else {
            allowedAction = false;
        }
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        
        player.update(timeClock);
        if(enemy.getLife() > 0)
            enemy.update(timeClock, allowedAction);

        window->clear();
        // window->draw(backgroundSprite);
        window->draw(floor);
        if(enemy.getLife() > 0)
            enemy.render();
        player.render();
        window->display();
    }

        
    return EXIT_SUCCESS;
}