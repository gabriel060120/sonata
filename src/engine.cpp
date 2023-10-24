#include <memory>
#include <iostream>

#include "engine.hpp"
#include "enemy.hpp"
#include "player.hpp"

void Engine::init() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720),"Plataforma 2D", sf:: Style::Titlebar | sf::Style::Close);
    window->setPosition(Vector2i(80,0));
    window->setFramerateLimit(120);
    
    // //engine controller
    fpsCounter = 0;
    heightFloor = 100.f;
    timeClock = 0.f;
    actionInterval = 1.f;
    timerToAction = 0.f;
    allowedAction = false;
    groundLocalization = window->getSize().y - heightFloor;

    //living elements
    player = std::make_shared<Player>(window.get(), groundLocalization);
    enemies.push_back(Enemy(window.get(), groundLocalization, player.get()));

    //sound effects
    if(!metronome.loadFromFile("./../audio/sound_effects/metronome.wav")){
        std::cout << std::endl << "Nao foi possivel carregar metronomo";
    }
    soundMetronome.setBuffer(metronome);

    //music
    pad.openFromFile("../audio/soundtracks/pad.wav");
    pad.setLoop(true);
    pad.setVolume(25);
    base1.openFromFile("../audio/soundtracks/base_100bpm.wav");
    base1.setLoop(true);
    seriePosition = 0;
    // serieMusic.openFromFile(series[seriePosition].getPathMusic());

    //text
    font.loadFromFile("../fonts/PixelBloated.ttf");
    fpsIndicator.setFont(font);
    fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
    fpsIndicator.setPosition(Vector2f(this->window->getSize().x - 150, 0));
    fpsIndicator.setScale(Vector2f(0.5f, 0.5f));

    //texture
    floor.setSize(Vector2f(this->window->getSize().x, heightFloor));
    floor.setFillColor(Color::Yellow);
    floor.setPosition(0.f, this->window->getSize().y - heightFloor);

}

void Engine::update() { 
    while(window->isOpen())
    {
        if(pad.getStatus() == sf::Music::Stopped) {
            pad.play();
        }
        if(base1.getStatus() == sf::Music::Stopped) {
            base1.play();
        }
        // if(serieMusic.getStatus() == sf::Music::Stopped) {
        //     serieMusic.play();
        // }
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
        player->update(timeClock, allowedAction);
        if(enemies[0].getLife() > 0)
            enemies[0].update(timeClock, allowedAction);
        
        
        window->clear();

        //draw
        // window->draw(backgroundSprite);
        window->draw(floor);
        window->draw(fpsIndicator);
        if(enemies[0].getLife() > 0)
            enemies[0].render();
        player->render();
        window->display();
    }
    
}

void Engine::setMusics() {
    // series.push_back(SerieMusic("../audio/soundtracks/serie_1-1_100bpm.wav",{1,1,1,1,1,-1,-2,1,1,1,0.5,0.5,1,-1,-2}));
}
