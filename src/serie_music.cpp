#include "serie_music.hpp"
#include <string>
#include <vector>
#include <iostream>

SerieMusic::SerieMusic(std::string pathMusic, std::vector<float> triggers) {
    this->pathMusic = pathMusic;
    this->triggers = triggers;
};

std::vector<float> SerieMusic::getTriggers() {
    return triggers;
}

std::string SerieMusic::getPathMusic() {
    return pathMusic;
}
