#include "enemy.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;

const String ENEMY_TEXTURE_IDLE = "./../assets/sprites/enemy/enemy_idle.png";
const String ENEMY_TEXTURE_MOVIMENT = "./../assets/sprites/enemy/enemy_moviment.png";
const String ENEMY_TEXTURE_PREPARING_ATTACK = "./../assets/sprites/enemy/enemy_preparing_attack.png";
const String ENEMY_TEXTURE_ATTACK = "./../assets/sprites/enemy/enemy_attack.png";
const int ENEMY_SPRITE_WIDHT = 24;
const int ENEMY_SPRITE_HEIGHT = 32;
const float FRAME_VELOCITY = 5;

Enemy::Enemy(RenderWindow* renderWindow, int groundLocalization, Player *player) {
    this->window = renderWindow;
    this->player = player;
    this->groundPosition = groundLocalization;
    setAnimData();
    init();
}

void Enemy::setAnimData() {
    // idle
    framesMax.push_back(11);
    textures.push_back(Texture());
    textures[SpriteAnim::Idle].loadFromFile(ENEMY_TEXTURE_IDLE);
    spriteWidth.push_back({24,24,24,24,24,24,24,24,24,24,24});
    spriteHeight.push_back(32);
    frameTime.push_back(10.f);
    
    // moviment
    framesMax.push_back(13);
    textures.push_back(Texture());
    textures[SpriteAnim::Moviment].loadFromFile(ENEMY_TEXTURE_MOVIMENT);
    spriteWidth.push_back({22,22,22,22,22,22,22,22,22,22,22,22,22});
    spriteHeight.push_back(33);
    frameTime.push_back(10.f);


    // preparing attack
    framesMax.push_back(5);
    textures.push_back(Texture());
    textures[SpriteAnim::PreparingAttack].loadFromFile(ENEMY_TEXTURE_PREPARING_ATTACK);
    spriteWidth.push_back({24,24,24,24,24});
    spriteHeight.push_back(37);
    frameTime.push_back(30.f);

    // attack
    framesMax.push_back(11);
    textures.push_back(Texture());
    textures[SpriteAnim::Attack].loadFromFile(ENEMY_TEXTURE_ATTACK);
    spriteWidth.push_back({40,31,32,32,32,33,32,27,23,21,22});
    spriteHeight.push_back(36);
    frameTime.push_back(40.f);

    sprite.setTexture(textures[SpriteAnim::Idle]);
    sprite.setTextureRect(IntRect(0,0,spriteWidth[SpriteAnim::Idle][0], spriteHeight[SpriteAnim::Idle]));
    sprite.setScale(4.0f, 4.0f);
}

void Enemy::init() {
    animStatus = SpriteAnim::Idle;
    frame = 0.f;
    previousFrame = 0;
    //timers
    gameClock = 0.0f;
    movimentSpeed = 200.f;
    dx = 0;
    dy = 0;
    attackDistance = 50;
    lifeBar = std::make_unique<LifeBar>(window, Vector2f(5.f, 10.f), 20, Vector2f(sprite.getPosition().x, sprite.getPosition().y - 30), Color::Red, Color(128,128,128));

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
    previousState = 0;

    setPosition(Vector2f(window->getSize().x, groundPosition - sprite.getGlobalBounds().height));
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

void Enemy::update(float clock, bool allowedAction, bool inIntervalAllowedAction, int gameStatus) {
    updateGameTime(clock, allowedAction);
    this->gameStatus = gameStatus;
    this->inIntervalAllowedAction = inIntervalAllowedAction;
    
    takeDamage();
    animation();
    if(previousState != state) {
        changeAction = true;
        previousState = state;
    } else {
        changeAction = false;
    }
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

void Enemy::animation() {
    float position = sprite.getPosition().x;
    if(changeAction) {
        sprite.setTexture(textures[animStatus]);
        if(animStatus != SpriteAnim::Moviment)
            position = finalPosition - spriteWidth[animStatus][0];
        setPosition(Vector2f(position, groundPosition - sprite.getGlobalBounds().height));
        frame = 0;
        previousFrame = 0;
        previousSpriteWidth = 0;
    }
        frame += frameTime[animStatus] * gameClock;
    if(frame >= (framesMax[animStatus]) && animStatus != SpriteAnim::PreparingAttack && animStatus != SpriteAnim::Attack) {
        frame = 0;
        previousFrame = 0;
        previousSpriteWidth = 0;
    }
    int intFrame = (int) frame;
    if(intFrame > previousFrame) {
        previousSpriteWidth += spriteWidth[animStatus][previousFrame];
        previousFrame = intFrame;
        if(animStatus != SpriteAnim::Moviment) {
            position = finalPosition - spriteWidth[animStatus][frame];
            // setPosition(Vector2f(position, groundPosition - sprite.getGlobalBounds().height));
        }
    }
    if((!(frame >= (framesMax[animStatus])) || (animStatus != SpriteAnim::PreparingAttack && animStatus != SpriteAnim::Attack)))
    sprite.setTextureRect(IntRect(previousSpriteWidth, 0, spriteWidth[animStatus][intFrame], spriteHeight[animStatus]));
    // sprite.setTextureRect(IntRect(spriteWidth[SpriteAnim::Attack][intFrame] * (int) intFrame, 0, spriteWidth[SpriteAnim::Attack][intFrame], spriteHeight[SpriteAnim::Attack]));

}


//=================================================================================================================================
//||---------------------------------------------------- actions ----------------------------------------------------------------||
//=================================================================================================================================

void Enemy::moviment() {
    inMoviment = true;
    animStatus = SpriteAnim::Moviment;


    if((player->sprite.getPosition().x + (attackDistance * 0.3) + player->sprite.getGlobalBounds().width) < sprite.getPosition().x) {
        dx = -movimentSpeed;
    } else {
        finalPosition = sprite.getPosition().x + spriteWidth[SpriteAnim::Idle][0];
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
    animStatus = SpriteAnim::PreparingAttack;

    if(allowedAction){
        std::cout <<"\x1B[31mInimigo: preparando ataque" << std::endl;
        inPreparingAttack = true;
        stateChanged = true;
        // sprite.setFillColor(Color(255,165,0));
    } 
    // else if(allowedAction && stateChanged) {
        // toAttack = true;
        // stateChanged = false;
        // toPreparingAttack = false;
        // inPreparingAttack = false;
    // }
}

void Enemy::attack() {
    animStatus = SpriteAnim::Attack;
    if(allowedAction){
        animStatus = SpriteAnim::PreparingAttack;
        std::cout <<"\x1B[31mInimigo: atacando" << std::endl;
        inAttacking = true;
        stateChanged = true;
        // sprite.setFillColor(Color::Red);
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
    animStatus = SpriteAnim::Idle;
    if(allowedAction && gameStatus == 2){
        // sprite.setFillColor(Color(128,128,128));
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
    if(sprite.getGlobalBounds().intersects(player->getAttackBox().getGlobalBounds()) 
        && !inTakingDamage 
        && player->inAttacking()
        && (allowedAction || inIntervalAllowedAction)
    ) {
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

int Enemy::getState() {
    return state;
}