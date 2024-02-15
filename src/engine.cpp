#include <memory>
#include <iostream>

#include "engine.hpp"
#include "enemy.hpp"
#include "player.hpp"

void Engine::init() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720),"SONATA v0.1", sf:: Style::Titlebar | sf::Style::Close);
    window->setPosition(Vector2i(80,0));
    window->setFramerateLimit(240);
    
    // //engine controller
    fpsCounter = 0;
    heightFloor = 100.f;
    timeClock = 0.f;
    timerToAction = 0.f;
    triggerIndex = 0;
    allowedAction = false;
    intervalAllowed = 0.07f;
    inIntervalAllowed = false;
    intervalAllowedTimer = 0.f;
    initAllowedTimer = false;
    groundLocalization = window->getSize().y - heightFloor;
    status = State::Preparing;
    firstChangeStatus = true;

    //living elements
    player = std::make_shared<Player>(window.get(), groundLocalization);
    enemies.push_back(Enemy(window.get(), groundLocalization, player.get()));

    //sound effects
    if(!metronome.loadFromFile("./../audio/sound_effects/metronome.wav")){
        // std::cout << std::endl << "Nao foi possivel carregar metronomo";
    }
    soundMetronome.setBuffer(metronome);

    //music
    setMusics();
    pad.openFromFile("../audio/soundtracks/pad.wav");
    pad.setVolume(25);
    pad.setLoop(true);
    base1.openFromFile("../audio/soundtracks/base_100bpm.wav");
    seriePosition = 0;
    serieMusic.openFromFile(series[seriePosition].getPathMusic());
    baseUnitTime = 60.f/series[seriePosition].getBpm();
    actionInterval = 0;

    //text
    font.loadFromFile("../fonts/arial.ttf");
    //FPS
    fpsIndicator.setFont(font);
    fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
    fpsIndicator.setPosition(Vector2f(this->window->getSize().x - 150, 0));
    fpsIndicator.setScale(Vector2f(0.5f, 0.5f));
    //Turn Indicator
    stateIndicator.setFont(font);
    stateIndicator.setString("Preparando");
    stateIndicator.setScale(Vector2f(1.f, 1.f));
    stateIndicator.setPosition(Vector2f((window->getSize().x - stateIndicator.getGlobalBounds().width)/ 2, 200));


    //texture
    floor.setSize(Vector2f(this->window->getSize().x, heightFloor));
    floor.setFillColor(Color::Yellow);
    floor.setPosition(0.f, this->window->getSize().y - heightFloor);

}

void Engine::update() {
    while(window->isOpen())
    {
        //Game Status
        statusControl();
        allowedAction = false;
        timeClock = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
        timerToAction += timeClock;
        timerUpdateFps += timeClock;
        fpsCounter = (1/timeClock) + 1;

        if(initAllowedTimer) {
            intervalAllowedTimer += timeClock;
        }
        if(timerUpdateFps >= 0.25) {
            timerUpdateFps = 0;
            fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
        }
        
        if(status == State::Preparing || status == State::Presentation) {
            actionInterval = baseUnitTime;
            if(timerToAction >= actionInterval) {
                allowedAction = true;
                timerToAction = 0.f;
                // soundMetronome.play();
                // cout << "\x1B[0m>> Gatilho <<" << endl;
            } 
        } else if(status == State::EnemyTurn || status == State::PlayerTurn) {
            if(firstChangeStatus) {
                actionInterval = 0.f;
                triggerIndex = 0;
            } 
            if(firstChangeStatus || timerToAction >= actionInterval) {
                getNextTimeAction();
                timerToAction = 0.f;
                // soundMetronome.play();
            }
            if((timerToAction >= (actionInterval - intervalAllowed)) && !inIntervalAllowed) {
                // std::cout << "================> inicio intervalo<================" << std::endl;
                inIntervalAllowed = true;
            }
            if(intervalAllowedTimer >= intervalAllowed) {
                inIntervalAllowed = false;
                initAllowedTimer= false;
                intervalAllowedTimer = 0.f;
                // std::cout << "================> fim intervalo<================" << std::endl;
            }
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
        player->update(timeClock, allowedAction, inIntervalAllowed, status);
        if(player->getLife() <= 0) {
            init();
        }
        if(enemies[0].getLife() > 0)
            enemies[0].update(timeClock, allowedAction, inIntervalAllowed, status);
        
        window->clear();

        //draw
        // window->draw(backgroundSprite);
        window->draw(floor);
        window->draw(fpsIndicator);
        window->draw(stateIndicator);
        if(enemies[0].getLife() > 0)
            enemies[0].render();
        // else
            // enemies.clear();
        player->render();
        window->display();
    }
    
}

void Engine::statusControl() {
    if(status == State::Preparing) {
        if(firstChangeStatus) {
            repeatBase();
            // std::cout << "================> Preparando <================" << std::endl;
            firstChangeStatus = false;
            stateIndicator.setString("Preparando");
            stateIndicator.setPosition(Vector2f((window->getSize().x - stateIndicator.getGlobalBounds().width)/ 2, 200));
        }
        if(enemies.size() == 0) {
            enemies.push_back(Enemy(window.get(), groundLocalization, player.get()));
        }
        if(!(base1.getStatus() == sf::Music::Playing) || (base1.getPlayingOffset() >= base1.getDuration())) {
            status = State::Presentation;
            firstChangeStatus = true;
        }
    }
    else if(status == State::Presentation) {
        if(firstChangeStatus) {
            // std::cout << "================> Apresentacao <================" << std::endl;
            repeatBase();
            serieMusic.play();
            stateIndicator.setString("Apresentacao");
            stateIndicator.setPosition(Vector2f((window->getSize().x - stateIndicator.getGlobalBounds().width)/ 2, 200));
            firstChangeStatus = false;
        }
        if(!(serieMusic.getStatus() == sf::Music::Playing) || (serieMusic.getPlayingOffset() >= serieMusic.getDuration())) {
            status = State::EnemyTurn;
            serieMusic.stop();
            firstChangeStatus = true;
        }
    }
    else if(status == State::EnemyTurn) {
        if(firstChangeStatus) {
            // std::cout << "================> Turno Inimigo <================" << std::endl;
            repeatBase();
            serieMusic.play();
            stateIndicator.setString("Turno Inimigo");
            stateIndicator.setPosition(Vector2f((window->getSize().x - stateIndicator.getGlobalBounds().width)/ 2, 200));
            firstChangeStatus = false;
        }
        if(!(serieMusic.getStatus() == sf::Music::Playing) || (serieMusic.getPlayingOffset() >= serieMusic.getDuration())) {
            status = State::PlayerTurn;
            serieMusic.stop();
            firstChangeStatus = true;
        }
    }
    else if(status == State::PlayerTurn) {
        if(firstChangeStatus) {
            // std::cout << "================> Turno Player <================" << std::endl;
            repeatBase();
            serieMusic.play();
            stateIndicator.setString("Seu Turno");
            stateIndicator.setPosition(Vector2f((window->getSize().x - stateIndicator.getGlobalBounds().width)/ 2, 200));
            enemies[0].setState(1);
            firstChangeStatus = false;
        }
        if(intervalAllowed)
        if(!(serieMusic.getStatus() == sf::Music::Playing) || (serieMusic.getPlayingOffset() >= serieMusic.getDuration())) {
            seriePosition++;

            if(seriePosition < ((int)series.size())) {
                serieMusic.stop();
                serieMusic.openFromFile(series[seriePosition].getPathMusic());
                triggerIndex = 0;
                // repeatBase();
                status = State::Presentation;
            } else {}

            // window->close();
        }
    }
}

void Engine::repeatBase() {
    pad.play();
    base1.stop();
    base1.play();
}

void Engine::getNextTimeAction() {
    int vectorSize = static_cast<int>(series[seriePosition].getTriggers().size());
    if(vectorSize > triggerIndex) {
        if(series[seriePosition].getTriggers()[triggerIndex] > 0) {
            actionInterval = series[seriePosition].getTriggers()[triggerIndex] * baseUnitTime;
            triggerIndex++;
            allowedAction = true;
            initAllowedTimer = true;
            // std::cout << "================> gatilho <================" << std::endl;
        } else {
            actionInterval = -series[seriePosition].getTriggers()[triggerIndex] * baseUnitTime;
            triggerIndex++;
        }
    } else {
        actionInterval = 100;
    }
}

//=================================================================================================================================
//||---------------------------------------------------- setters ----------------------------------------------------------------||
//=================================================================================================================================

void Engine::setMusics() {
    series.push_back(SerieMusic("../audio/soundtracks/serie_1-1_100bpm.wav",{1,1,1,-1,1,0.5,0.5,1,-1,0.5,0.5,1,1,-1,0.5,0.5,0.5,0.5,0.5,-1.5}, 100));
    series.push_back(SerieMusic("../audio/soundtracks/serie_1-2_100bpm.wav",{0.5,0.5,0.5,0.5,1,0.5,-0.5,1,0.5,0.5,0.5,0.5,0.5,-0.5,0.5,0.5,1,1,0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5}, 100));
    series.push_back(SerieMusic("../audio/soundtracks/serie_1-3_100bpm.wav",{1,0.5,0.5,1,0.5,-0.5,2,0.5,0.5,0.5,-0.5,1,0.5,0.5,1,0.5,-0.5,2,0.5,0.5,0.5,-0.5}, 100));
}

void Engine::setStatus(State newStatus) {
    status = newStatus;
}