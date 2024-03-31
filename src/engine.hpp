#pragma once
#define ENGINE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

#include "player.hpp"
#include "enemy.hpp"
#include "serie_music.hpp"
#include "finish_page.hpp"

using namespace sf;

class Engine {
    public:
        enum State {
            Preparing,
            Presentation,
            EnemyTurn,
            PlayerTurn    
        };
        void init();
        void restart();
        void update();
        //setters
        void setStatus(State newStatus);

    private:
        //engine controller
        std::shared_ptr<sf::RenderWindow> window;
        std::unique_ptr<FinishPage> finishPage;
        bool finishGame;
        int fpsCounter;
        float timerUpdateFps;
        float heightFloor;
        float timeClock;
        float actionInterval;
        float baseUnitTime;
        float timerToAction;
        Clock gameClock;
        bool allowedAction;
        float intervalAllowed;
        float intervalAllowedTimer;
        bool initAllowedTimer;
        bool inIntervalAllowed;
        int triggerIndex;
        int groundLocalization;
        State status;
        bool firstChangeStatus;
        bool repeatCompass;
        void statusControl();
        void getNextTimeAction();
        //living elements
        std::shared_ptr<Player> player;
        std::vector<Enemy> enemies;
        //sound effects
        sf::SoundBuffer metronome;
        sf::Sound soundMetronome;
        //music
        sf::Music pad;
        sf::Music base1;
        std::vector<SerieMusic> series;
        sf::Music serieMusic;
        int seriePosition;
        void setMusics();
        void repeatBase();
        //text
        sf::Font font;
        sf::Text fpsIndicator;
        sf::Text stateIndicator;
        //texture
        // Texture floorTexture;
        RectangleShape floor;

};