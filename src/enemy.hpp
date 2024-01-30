#pragma once
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "life_bar.hpp"
using namespace sf;

class Enemy{
    private:
        RenderWindow* window;
        Player * player;
        std::unique_ptr<LifeBar> lifeBar;

        enum SpriteAnim {
            Idle,
            Moviment,
            PreparingAttack,
            Attack    
        };

        //game timers
        float gameClock;

        //moviment
        float movimentSpeed;
        float dx, dy;
        int attackDistance;

        //action timers
        float timePreparingAttack;
        float timeAttack;
        float timerAction;

        // animation
        std::vector<sf::Texture> textures;
        SpriteAnim animStatus;
        std::vector<int> framesMax;
        std::vector<std::vector<int>> spriteWidth;
        std::vector<int> spriteHeight;
        std::vector<float> frameTime;
        void setAnimData();
        float frame;
        int previousFrame;
        int previousSpriteWidth;
        float finalPosition;

        // actions control
        bool allowedAction;
        bool inIntervalAllowedAction;
        float allowedActionTime;
        bool changeAction;
        bool inIdle;
        bool inMoviment;
        bool inPreparingAttack;
        bool inAttacking;
        bool inTakingDamage;
        bool toIdle;
        bool toPreparingAttack;
        bool toAttack;
        bool toTakingDamage;
        bool stateChanged;
        int state;
        int previousState;
        int gameStatus;

        int groundPosition;
        FloatRect rect;
        
    public:
        Sprite sprite;

        Enemy(RenderWindow* renderWindow, int groundLocalization, Player * player);

        void init();
        void setPosition(sf::Vector2f position);
        void updateGameTime(float clock, bool allowedAction);
        void update(float clock, bool allowedAction, bool inIntervalAllowedAction, int gameStatus);
        
        void animation();
        
        //actions
        void idle();
        void moviment();
        void preparingAttack();
        void attack();
        //reactions
        void takeDamage();
        //getters
        int getLife();
        int getState();
        //render object
        void render();
};