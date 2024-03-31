#include "enemy.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;

// const String ENEMY_TEXTURE = "./assets/sprites/Enemy/idle.png";
const int ENEMY_SPRITE_WIDHT = 50;
const int ENEMY_SPRITE_HEIGHT = 37;
const float FRAME_VELOCITY = 5;

Enemy::Enemy(RenderWindow* renderWindow, int groundLocalization, Player *player) {
    this->window = renderWindow;
    this->player = player;
    this->groundPosition = groundLocalization;
    init();
}

void Enemy::init() {
    sprite.setSize(Vector2f(100.f, 100.f));
    sprite.setFillColor(Color(128,128,128));
    frame = 0.f;
    //timers
    gameClock = 0.0f;
    movimentSpeed = 200.f;
    dx = 0;
    dy = 0;
    attackDistance = 50;
    lifeBar = std::make_unique<LifeBar>(window, Vector2f(1.f, 10.f), 100, Vector2f(sprite.getPosition().x, sprite.getPosition().y - 30), Color::Red, Color(128,128,128));

    //action timers
    timePreparingAttack = 1.f;
    timeAttack = 1.f;
    timerAction = 0.f;
    allowedActionTime = 15;
    //action controllers
    inMoviment = true;
    inTakingDamage = false;
    inPreparingAttack = false;
    inAttacking = false;
    changeAction = false;
    stateChanged = false;
    toPreparingAttack = false;
    toAttack = false;
    toTakingDamage = false;
    state = -1;

    groundPosition -= sprite.getGlobalBounds().height;
    setPosition(Vector2f(window->getSize().x, groundPosition));
}

void Enemy:: restart() {
    sprite.setFillColor(Color(128,128,128));
    frame = 0.f;
    //timers
    gameClock = 0.0f;
    movimentSpeed = 200.f;
    dx = 0;
    dy = 0;
    attackDistance = 50;
    lifeBar->refresh();

    //action timers
    timePreparingAttack = 1.f;
    timeAttack = 1.f;
    timerAction = 0.f;
    allowedActionTime = 15;
    //action controllers
    inMoviment = true;
    inTakingDamage = false;
    inPreparingAttack = false;
    inAttacking = false;
    changeAction = false;
    stateChanged = false;
    toPreparingAttack = false;
    toAttack = false;
    toTakingDamage = false;
    state = -1;

    setPosition(Vector2f(window->getSize().x, groundPosition));
}

void Enemy::updateGameTime(float clock, bool allowedAction) {
    this->gameClock = clock;
    this->allowedAction = allowedAction;
}

void Enemy::setPosition(Vector2f position) {
    sprite.setPosition(position);
    lifeBar->setPosition(Vector2f(position.x, position.y - 20));
}

void Enemy::render() {
    window->draw(sprite);
    lifeBar->render();
}

void Enemy::update(float clock, bool allowedAction, bool inIntervalAllowedAction, int gameStatus) {
    updateGameTime(clock, allowedAction);
    this->gameStatus = gameStatus;
    this->inIntervalAllowedAction = inIntervalAllowedAction;
    
    takeDamage();

    if(inMoviment) {
        state = -1;
        moviment(); 
    } else if(allowedAction) {
        if(state >= 2 || gameStatus != 2) {
            state = 0;
        } else {
         state++;
        }
    }

    switch (state)
    {
    case 0:
        idle();
        break;
    case 1:
        preparingAttack();
        break;
    case 2:
        attack();
        break;
    
    default:
        break;
    }    
}

//=================================================================================================================================
//||---------------------------------------------------- actions ----------------------------------------------------------------||
//=================================================================================================================================

void Enemy::moviment() {
    inMoviment = true;

    if((player->sprite.getPosition().x - attackDistance) > (sprite.getPosition().x + sprite.getGlobalBounds().width)) {
        dx = movimentSpeed;
        
        frame += FRAME_VELOCITY * gameClock;
        if(frame > 3) {
            frame -= 3;
        }
    } else if((player->sprite.getPosition().x + attackDistance + player->sprite.getGlobalBounds().width) < sprite.getPosition().x) {
        dx = -movimentSpeed;
        frame += FRAME_VELOCITY * gameClock;
        if(frame > 3) {
            frame -= 3;
        }
    } else {
        dx = 0;
        state = 0;
        inMoviment = false;
        toIdle = true;
    }

    sprite.move(dx * gameClock, 0.f);
    lifeBar->setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20));
}

void Enemy::preparingAttack() {
    timerAction += gameClock;

    if(allowedAction){
        inPreparingAttack = true;
        stateChanged = true;
        sprite.setFillColor(Color(255,165,0));
    } 
}

void Enemy::attack() {
    if(allowedAction){
        inAttacking = true;
        stateChanged = true;
        sprite.setFillColor(Color::Red);
        player->takeDamage(1);
    } 
}

void Enemy::idle() {
    if(allowedAction){
        sprite.setFillColor(Color(128,128,128));
        inIdle = true;
        stateChanged = true;
    } 
}

//=================================================================================================================================
//||--------------------------------------------------- reactions ---------------------------------------------------------------||
//=================================================================================================================================

void Enemy::takeDamage() {
    if(sprite.getGlobalBounds().intersects(player->getAttackBox().getGlobalBounds()) 
        && !inTakingDamage 
        && player->inAttacking()
        && (allowedAction || inIntervalAllowedAction)
    ) {
        inTakingDamage = true;
        lifeBar->takeDamage(1);
    } else {
        inTakingDamage = false;
    }
}

//=================================================================================================================================
//||---------------------------------------------------- getters ----------------------------------------------------------------||
//=================================================================================================================================

int Enemy::getLife() {
    return lifeBar->getLife();
}

int Enemy::getState() {
    return state;
}

//=================================================================================================================================
//||---------------------------------------------------- setters ----------------------------------------------------------------||
//=================================================================================================================================

void Enemy::setState(int newState) {
    this->state = state; 
}