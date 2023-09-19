#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include "player.hpp"
#include "enemy.hpp"

using namespace std;
using namespace sf;

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720),"Plataforma 2D", sf:: Style::Titlebar | sf::Style::Close);
    window->setPosition(Vector2i(80,0));
    // window->setFramerateLimit(120);
    int fpsCounter = 0;
    float timerUpdateFps;
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

    //sound effects
    sf::SoundBuffer metronome;
    sf::Sound soundMetronome;
    if(!metronome.loadFromFile("./../audio/sound_effects/metronome.wav")){
        std::cout << std::endl << "Nao foi possivel carregar metronomo";
    }
    soundMetronome.setBuffer(metronome);

    //text
    sf::Font font;
    sf::Text fpsIndicator;
    font.loadFromFile("../fonts/PixelBloated.ttf");
    fpsIndicator.setFont(font);
    fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
    fpsIndicator.setPosition(Vector2f(window->getSize().x - 150, 0));
    fpsIndicator.setScale(Vector2f(0.5f, 0.5f));

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
        timerUpdateFps += timeClock;
        fpsCounter = (1/timeClock) + 1;

        if(timerUpdateFps >= 0.25) {
            timerUpdateFps = 0;
            fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
        }
        if(timerToAction >= actionInterval) {
            allowedAction = true;
            timerToAction = 0.f;
            // soundMetronome.play();
            // cout << "\x1B[0m>> Gatilho <<" << endl;
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
        //updates
        player.update(timeClock, allowedAction);
        if(enemy.getLife() > 0)
            enemy.update(timeClock, allowedAction);
        
        
        window->clear();

        //draw
        // window->draw(backgroundSprite);
        window->draw(floor);
        window->draw(fpsIndicator);
        if(enemy.getLife() > 0)
            enemy.render();
        player.render();
        window->display();
    }

        
    return EXIT_SUCCESS;
}