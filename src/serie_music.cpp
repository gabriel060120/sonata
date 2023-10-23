#include "serie_music.hpp"
#include <string>
#include <vector>
#include <iostream>

SerieMusic::SerieMusic(std::string pathMusic, std::vector<float> triggers) {
    this->pathMusic = pathMusic;
    this->triggers = triggers;
    
    if(!this->music.openFromFile(pathMusic)) {
        std::cout << "Nao foi possivel carregar a imagem" << std::endl;
    }
};

std::vector<float> SerieMusic::getTriggers() {
    return triggers;
}
