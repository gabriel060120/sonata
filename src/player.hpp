#pragma once
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "life_bar.hpp"

using namespace sf;

class Player {
    public:
        // Sprite sprite;
        RectangleShape sprite;

        Player(RenderWindow* renderWindow, int groundLocalization);

        void restart();
        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock, bool triggerAction);
        void init();
        void update(float clock, bool triggerAction, bool inTriggerAction, int gameStatus);
        //actions
        void actions();
        void block();
        void attack();
        void moviment();
        void idle();
        void longSleep();
        void shortSleep();
        //getters
        RectangleShape getAttackBox();
        bool inAttacking();
        bool inBlocking();
        int getLife();
        //reactions
        void takeDamage(int valueDamage);

        void render();

    private:
        RenderWindow* window;
        Texture texture;
        //game
        float frame;
        float gameTime;
        bool triggerAction;
        bool inTriggerActionInterval;
        int gameStatus;
        //action        
        float movimentSpeed;
        float dx, dy;
        float timerActionTransition;
        float actiontransitionTime;
        int actionIndex;
        bool hitTrigger;
        RectangleShape attackBox;
        bool attackingAction;
        bool toTakingDamage;
        bool blockingAction;
        bool longSleepingAction;
        bool shortSleepingAction;
        //sound
        sf::SoundBuffer blockSoundBuffer;
        sf::Sound blockSound;
        sf::SoundBuffer attackSoundBuffer;
        sf::Sound attackSound;
        sf::SoundBuffer errorSoundBuffer;
        sf::Sound errorSound;

        int groundPosition;
        FloatRect rect;

        std::unique_ptr<LifeBar> lifeBar; 

};