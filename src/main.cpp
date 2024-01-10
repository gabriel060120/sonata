#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include "player.hpp"
#include "enemy.hpp"
#include "serie_music.hpp"
#include "engine.hpp"

using namespace std;
using namespace sf;


int main() {
    
    auto engine = make_unique<Engine>();
    engine->init();
    engine->update();

    return EXIT_SUCCESS;
}