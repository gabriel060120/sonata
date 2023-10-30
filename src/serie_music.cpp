#include "serie_music.hpp"
#include <string>
#include <vector>
#include <iostream>

SerieMusic::SerieMusic(std::string pathMusic, std::vector<float> triggers, int compassSize, int bpm) {
    this->pathMusic = pathMusic;
    this->triggers = triggers;
    this->compassSize = compassSize;
    this->bpm = bpm;
};

//=================================================================================================================================
//||---------------------------------------------------- getters ----------------------------------------------------------------||
//=================================================================================================================================

std::vector<float> SerieMusic::getTriggers() {
    return triggers;
}

std::string SerieMusic::getPathMusic() {
    return pathMusic;
}

int SerieMusic::getBpm() {
    return bpm;
}