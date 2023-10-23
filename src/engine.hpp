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
        int seriePosition;
        //text
        sf::Font font;
        sf::Text fpsIndicator;
        //texture
        // Texture floorTexture;
        RectangleShape floor;





    public:
        void init();
        void update();
};