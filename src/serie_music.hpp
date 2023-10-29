#pragma once
#define SERIE_MUSIC_H
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class SerieMusic {
    private:
        int bpm;
        int compassSize;
        std::vector<float> triggers;
        std::string pathMusic;
    
    public:
        SerieMusic(std::string pathMusic, std::vector<float> triggers, int compassSize, int bpm);
        std::vector<float> getTriggers();
        std::string getPathMusic();
};