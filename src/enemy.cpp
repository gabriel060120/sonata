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
    // texture.loadFromFile(ENEMY_TEXTURE);
    // sprite.setTexture(texture);
    // sprite.setTexture(texture);
    sprite.setSize(Vector2f(100.f, 100.f));
    sprite.setFillColor(Color(128,128,128));
    frame = 0.f;
    //timers
    gameClock = 0.0f;
    movimentSpeed = 200.f;
    dx = 0;
    dy = 0;
    attackDistance = 50;
    lifeBar = std::make_unique<LifeBar>(window, Vector2f(20.f, 10.f), 5, Vector2f(sprite.getPosition().x, sprite.getPosition().y - 30), Color::Red, Color(128,128,128));

    //action timers
    timePreparingAttack = 1.f;
    timeAttack = 1.f;
    timerAction = 0.f;
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


    this->groundPosition = groundLocalization - sprite.getGlobalBounds().height;
    // sprite.setTextureRect(IntRect(0, groundPosition, ENEMY_SPRITE_WIDHT, ENEMY_SPRITE_HEIGHT));
    setPosition(Vector2f(window->getSize().x, groundPosition));


}

void Enemy::updateGameTime(float clock, bool allowedAction) {
    this->gameClock = clock;
    this->allowedAction = allowedAction;
    //  if(allowedAction)
        // std::cout <<"\x1B[31mInimigo: acao habilitada" << std::endl;

}

void Enemy::setPosition(Vector2f position) {
    sprite.setPosition(position);
    lifeBar->setPosition(Vector2f(position.x, position.y - 20));
}

void Enemy::render() {
    window->draw(sprite);
    lifeBar->render();
}

void Enemy::update(float clock, bool allowedAction) {
    updateGameTime(clock, allowedAction);
    
    takeDamage();

    if(inMoviment) {
        moviment(); 
    } else if(allowedAction) {
        if(state >= 2) {
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
        // sprite.move(movimentSpeed * gameClock, 0.f);
        
        frame += FRAME_VELOCITY * gameClock;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(ENEMY_SPRITE_WIDHT * (int) frame, 0, ENEMY_SPRITE_WIDHT,ENEMY_SPRITE_HEIGHT));
    } else if((player->sprite.getPosition().x + attackDistance + player->sprite.getGlobalBounds().width) < sprite.getPosition().x) {
        dx = -movimentSpeed;
        // sprite.move(-movimentSpeed * gameClock, 0.f);
        frame += FRAME_VELOCITY * gameClock;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(ENEMY_SPRITE_WIDHT * (int) frame + ENEMY_SPRITE_WIDHT, 0, -ENEMY_SPRITE_WIDHT,ENEMY_SPRITE_HEIGHT));
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
        std::cout <<"\x1B[31mInimigo: preparando ataque" << std::endl;
        inPreparingAttack = true;
        stateChanged = true;
        sprite.setFillColor(Color(255,165,0));
    } 
    // else if(allowedAction && stateChanged) {
        // toAttack = true;
        // stateChanged = false;
        // toPreparingAttack = false;
        // inPreparingAttack = false;
    // }
}

void Enemy::attack() {
    if(allowedAction){
        std::cout <<"\x1B[31mInimigo: atacando" << std::endl;
        inAttacking = true;
        stateChanged = true;
        sprite.setFillColor(Color::Red);
        player->takeDamage(1);
    } 
    // else if(allowedAction && stateChanged) {
        // toIdle = true;
        // stateChanged = false;
        // toAttack = false;
        // inAttacking = false;
    // }
}

void Enemy::idle() {
    if(allowedAction){
        sprite.setFillColor(Color(128,128,128));
        std::cout <<"\x1B[31mInimigo: parado" << std::endl;
        inIdle = true;
        stateChanged = true;
    } 
    // else if(allowedAction && stateChanged) {
        // toPreparingAttack = true;
        // stateChanged = false;
        // toIdle = false;
        // inIdle = false;
    // }
}

//=================================================================================================================================
//||--------------------------------------------------- reactions ---------------------------------------------------------------||
//=================================================================================================================================

void Enemy::takeDamage() {
    if(sprite.getGlobalBounds().intersects(player->getAttackBox().getGlobalBounds()) && !inTakingDamage && player->inAttacking()) {
        inTakingDamage = true;
        lifeBar->takeDamage(1);
        std::cout << "\x1B[31mInimigo: recebeu dano" << std::endl;
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