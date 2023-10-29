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

using namespace sf;

class Engine {
    public:
        enum Status {
            Preparing,
            Presentation,
            EnemyTurn,
            PlayerTurn    
        };
        void init();
        void update();
        //setters
        void setStatus(Status newStatus);

    private:
        //engine controller
        std::shared_ptr<sf::RenderWindow> window;
        int fpsCounter;
        float timerUpdateFps;
        float heightFloor;
        float timeClock;
        float actionInterval;
        float timerToAction;
        Clock gameClock;
        bool allowedAction;
        int groundLocalization;
        Status status;
        bool firstChangeStatus;
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
        //texture
        // Texture floorTexture;
        RectangleShape floor;





    
};