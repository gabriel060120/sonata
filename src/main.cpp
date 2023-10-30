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
// int main() {
//     auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720),"Plataforma 2D", sf:: Style::Titlebar | sf::Style::Close);
//     window->setPosition(Vector2i(80,0));
//     // window->setFramerateLimit(120);
//     int fpsCounter = 0;
//     float timerUpdateFps;
//     const float heightFloor = 100.f;
//     float timeClock = 0.f;
//     float actionInterval = 1.f;
//     float timerToAction = 0.f;
//     Clock gameClock;
//     bool allowedAction = false;

//     int groundLocalization = window->getSize().y - heightFloor;

//     Player player(window.get(), groundLocalization);
//     Enemy enemy(window.get(), groundLocalization, &player);

//     // Texture backgroundTexture;
//     // backgroundTexture.loadFromFile("./assets/img/bg.jpg");
//     // Sprite backgroundSprite(backgroundTexture);

//     //sound effects
//     sf::SoundBuffer metronome;
//     sf::Sound soundMetronome;
//     if(!metronome.loadFromFile("./../audio/sound_effects/metronome.wav")){
//         std::cout << std::endl << "Nao foi possivel carregar metronomo";
//     }
//     soundMetronome.setBuffer(metronome);

//     //music
//     sf::Music pad;
//     pad.openFromFile("../audio/soundtracks/pad.wav");
//     pad.setLoop(true);
//     pad.setVolume(25);
//     sf::Music base1;
//     base1.openFromFile("../audio/soundtracks/base_100bpm.wav");
//     base1.setLoop(true);
//     // pad.setVolume(50);
//     int seriePosition = 0;
//     sf::Music serieMusic;
//     SerieMusic series("../audio/soundtracks/serie_1-1_100bpm.wav",
//         {1,1,1,1,1,-1,-2,1,1,1,0.5,0.5,1,-1,-2});
//     serieMusic.openFromFile("../audio/soundtracks/serie_1-1_100bpm.wav");
//     serieMusic.setLoop(true);
//     // pad.setVolume(50);


//     //text
//     sf::Font font;
//     sf::Text fpsIndicator;
//     font.loadFromFile("../fonts/PixelBloated.ttf");
//     fpsIndicator.setFont(font);
//     fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
//     fpsIndicator.setPosition(Vector2f(window->getSize().x - 150, 0));
//     fpsIndicator.setScale(Vector2f(0.5f, 0.5f));

//     // Texture floorTexture;
//     RectangleShape floor(Vector2f(window->getSize().x, heightFloor));
//     floor.setFillColor(Color::Yellow);
//     // floorTexture.loadFromFile("./assets/img/floormax.jpg");
//     // Sprite floorSprite(floorTexture);
//     floor.setPosition(0.f, window->getSize().y - heightFloor);
    
//     while(window->isOpen())
//     {
//         if(pad.getStatus() == sf::Music::Stopped) {
//             pad.play();
//         }
//         if(base1.getStatus() == sf::Music::Stopped) {
//             base1.play();
//         }
//         if(serieMusic.getStatus() == sf::Music::Stopped) {
//             serieMusic.play();
//         }
//         timeClock = gameClock.getElapsedTime().asSeconds();
//         gameClock.restart();
//         timerToAction += timeClock;
//         timerUpdateFps += timeClock;
//         fpsCounter = (1/timeClock) + 1;

//         if(timerUpdateFps >= 0.25) {
//             timerUpdateFps = 0;
//             fpsIndicator.setString(std::to_string(fpsCounter) + "FPS");
//         }
//         if(timerToAction >= actionInterval) {
//             allowedAction = true;
//             timerToAction = 0.f;
//             // soundMetronome.play();
//             // cout << "\x1B[0m>> Gatilho <<" << endl;
//         } else {
//             allowedAction = false;
//         }
//         sf::Event event;
//         while(window->pollEvent(event))
//         {
//             if(event.type == sf::Event::Closed)
//             {
//                 window->close();
//             }
//         }
//         //updates
//         player.update(timeClock, allowedAction);
//         if(enemy.getLife() > 0)
//             enemy.update(timeClock, allowedAction);
        
        
//         window->clear();

//         //draw
//         // window->draw(backgroundSprite);
//         window->draw(floor);
//         window->draw(fpsIndicator);
//         if(enemy.getLife() > 0)
//             enemy.render();
//         player.render();
//         window->display();
//     }

        
//     return EXIT_SUCCESS;
// }