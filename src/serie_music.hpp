#pragma once
#define SERIE_MUSIC_H
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

using namespace sf;

class SerieMusic {
    private:
        int bpm;
        std::vector<float> triggers;
        std::string pathMusic;
    
    public:
        sf::Music music;
    
        SerieMusic(std::string pathMusic, std::vector<float> triggers);
        std::vector<float> getTriggers();
        sf::Music getMusic();
};