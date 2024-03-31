#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;

const int PLAYER_SPRITE_WIDHT = 50;
const int PLAYER_SPRITE_HEIGHT = 37;
const float FRAME_VELOCITY = 5;

Player::Player(RenderWindow* renderWindow, int groundLocalization) {
    //game
    window = renderWindow;
    this->groundPosition = groundLocalization;
    init();
}

void Player::init() {
    //player components
    sprite.setSize(Vector2f(window->getSize().y * 0.13, window->getSize().y * 0.13));
    sprite.setFillColor(Color::White);
    groundPosition -= sprite.getGlobalBounds().height;
    setPosition(Vector2f((window->getSize().x/2) - sprite.getGlobalBounds().width - 25 , groundPosition));

    lifeBar = std::make_unique<LifeBar>(window, Vector2f(window->getSize().x * 0.023, 30.f), 10, Vector2f(30, 50), Color::Green, Color(128,128,128));

    attackBox.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    attackBox.setFillColor(Color(255,0,0,128));
    attackBox.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite.getPosition().y);

    // game controller
    frame = 0.f;
    gameTime = 0.0f;
    movimentSpeed = 300.f;
    dx = 0;
    dy = 0;

    //actions controller
    actionIndex = 0;
    timerActionTransition = 0.f;
    actiontransitionTime = 0.25;
    attackingAction = false;
    blockingAction = false;
    longSleepingAction = false;
    shortSleepingAction = false;
    hitTrigger = false;

    //sound effects
    //block
    if(!blockSoundBuffer.loadFromFile("./../audio/sound_effects/player_block.wav")){
        std::cout << std::endl << "Nao foi possivel carregar som bloqueio";
    }
    blockSound.setBuffer(blockSoundBuffer);
    //attack
    if(!attackSoundBuffer.loadFromFile("./../audio/sound_effects/sword_attack.wav")){
        std::cout << std::endl << "Nao foi possivel carregar som ataque";
    }
    attackSound.setBuffer(attackSoundBuffer);
    //error
    if(!errorSoundBuffer.loadFromFile("./../audio/sound_effects/error.wav")){
        std::cout << std::endl << "Nao foi possivel carregar som de erro";
    }
    errorSound.setBuffer(errorSoundBuffer);
}

void Player::restart() {
    //player components
    sprite.setFillColor(Color::White);

    lifeBar->refresh();

    // game controller
    frame = 0.f;
    gameTime = 0.0f;
    movimentSpeed = 300.f;
    dx = 0;
    dy = 0;

    //actions controller
    actionIndex = 0;
    timerActionTransition = 0.f;
    actiontransitionTime = 0.25;
    attackingAction = false;
    blockingAction = false;
    longSleepingAction = false;
    shortSleepingAction = false;
    hitTrigger = false;

}

void Player::updateGameTime(float clock, bool triggerAction) {
    gameTime = clock;
    this->triggerAction = triggerAction;
}

void Player::setPosition(Vector2f position) {
    sprite.setPosition(position);
}

void Player::render() {
    window->draw(sprite);
    if(actionIndex == 2)
        window->draw(attackBox);
    lifeBar->render();
}

void Player::update(float clock, bool triggerAction, bool inTriggerAction, int gameStatus) {
    this->gameStatus = gameStatus;
    this->inTriggerActionInterval = inTriggerAction;
    updateGameTime(clock, triggerAction);

    actions();
}

//=================================================================================================================================
//||---------------------------------------------------- actions ----------------------------------------------------------------||
//=================================================================================================================================
void Player::actions() {
    if(actionIndex != 0) {
        timerActionTransition += gameTime;
        attackingAction = false;
        blockingAction = false;
    }
    if(actionIndex == 2 || actionIndex == 1) {
        if(inTriggerActionInterval) {
            hitTrigger = true;
        }
    }
    if(toTakingDamage) {
        if(inTriggerActionInterval) {
            
            if(actionIndex == 1) {
                toTakingDamage = false;
            }
        } else {
            lifeBar->takeDamage(1);
            toTakingDamage = false;
        }
    }
    if(!inTriggerActionInterval) {
        blockingAction = false;
        attackingAction = false;
    }
    if(timerActionTransition >= actiontransitionTime) {
        timerActionTransition = 0;
    }
    if(timerActionTransition == 0) {
        hitTrigger = false;
        if(shortSleepingAction) {
            shortSleep();
        }else if(longSleepingAction) {
            longSleep();
        }else if((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && gameStatus == 3) {
            attack();
        } else if((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && gameStatus == 2) {
            block();
        } else {
            idle();
        }
    }
}

void Player::idle() {
    actionIndex = 0;
    actiontransitionTime = 0.25;
    if(sprite.getFillColor() != Color::White)
        sprite.setFillColor(Color::White);
}
void Player::block() {
    actionIndex = 1;
    actiontransitionTime = 0.15;
    if(sprite.getFillColor() != Color::Blue) {
        sprite.setFillColor(Color::Blue);
    }
    if(inTriggerActionInterval) {
        blockSound.play();
        blockingAction = true;
    } else {
        errorSound.play();
        longSleepingAction = true;
    }
}
void Player::attack() {
    actionIndex = 2;
    actiontransitionTime = 0.15;
    if(sprite.getFillColor() != Color::Red) {
        sprite.setFillColor(Color::Red);
    }
    if(inTriggerActionInterval) {
        attackSound.play();
        attackingAction = true;
    } else {
        errorSound.play();
        longSleepingAction = true;
    }
}

void Player::longSleep() {
    actiontransitionTime = 1.0f;
    actionIndex = 3;
    longSleepingAction = false;
    if(sprite.getFillColor() != Color(238,130,238)) 
        sprite.setFillColor(Color(238,130,238));
}

void Player::shortSleep() {
    actiontransitionTime = 0.05;
    actionIndex = 4;
    shortSleepingAction = false;
    if(sprite.getFillColor() != Color(123,104,238)) 
        sprite.setFillColor(Color(123,104,238));
}

//=================================================================================================================================
//||--------------------------------------------------- reactions ---------------------------------------------------------------||
//=================================================================================================================================

void Player::takeDamage(int valueDamage) {
    if(actionIndex != 1) {
        toTakingDamage = true;
    }
}

//=================================================================================================================================
//||---------------------------------------------------- getters ----------------------------------------------------------------||
//=================================================================================================================================

RectangleShape Player::getAttackBox() {
    return attackBox;
}

bool Player::inAttacking() {
    return attackingAction;
}
bool Player::inBlocking() {
    return blockingAction;
}

int Player::getLife() {
    return lifeBar->getLife();
}