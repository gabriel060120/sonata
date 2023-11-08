#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;

// const String PLAYER_TEXTURE = "./assets/sprites/player/idle.png";
const int PLAYER_SPRITE_WIDHT = 50;
const int PLAYER_SPRITE_HEIGHT = 37;
const float FRAME_VELOCITY = 5;

Player::Player(RenderWindow* renderWindow, int groundLocalization) {
    //game
    window = renderWindow;
    // texture.loadFromFile(PLAYER_TEXTURE);
    // sprite.setTexture(texture);
    // sprite.setTexture(texture);

    //player components
    sprite.setSize(Vector2f(100.f, 100.f));
    sprite.setFillColor(Color::White);
    this->groundPosition = groundLocalization - sprite.getGlobalBounds().height;
    // sprite.setTextureRect(IntRect(0, groundPosition, PLAYER_SPRITE_WIDHT, PLAYER_SPRITE_HEIGHT));
    setPosition(Vector2f((window->getSize().x/2) - sprite.getGlobalBounds().width - 50 , groundPosition));

    lifeBar = std::make_unique<LifeBar>(window, Vector2f(60.f, 30.f), 5, Vector2f(30, 50), Color::Green, Color(128,128,128));

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
            std::cout << "\x1B[32mConfia na call princeso" << std::endl; 
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
    if(timerActionTransition >= actiontransitionTime) {
        timerActionTransition = 0;
        if(actionIndex == 1 || actionIndex == 2) {
            // switch (hitTrigger) {
                // case true:
                    shortSleepingAction = true;
                    longSleepingAction = false;
                    // break;
                // case false:
                    // shortSleepingAction = false;
                    // longSleepingAction = true;
                    // break;

            // } 
        }
    }
    if(timerActionTransition == 0) {
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
    std::cout << "\x1B[32mPlayer: bloqueando" << std::endl; 
    actionIndex = 1;
    actiontransitionTime = 0.15;
    blockingAction = true;
    blockSound.play();
    if(sprite.getFillColor() != Color::Blue) {
        sprite.setFillColor(Color::Blue);
        // longSleepingAction = true;
    }
    if(inTriggerActionInterval) {
    }
}
void Player::attack() {
    actionIndex = 2;
    actiontransitionTime = 0.15;
    attackingAction = true;
    attackSound.play();
    if(sprite.getFillColor() != Color::Red) {
        sprite.setFillColor(Color::Red);
        // longSleepingAction = true;
    }
    if(triggerAction) {
        // longSleepingAction = false;
    }
}

void Player::longSleep() {
    std::cout << "\x1B[32mPlayer: pausa longa" << std::endl; 
    actiontransitionTime = 0.5;
    actionIndex = 3;
    longSleepingAction = false;
    if(sprite.getFillColor() != Color(238,130,238)) 
        sprite.setFillColor(Color(238,130,238));
}

void Player::shortSleep() {
    std::cout << "\x1B[32mPlayer: pausa curta" << std::endl; 
    actiontransitionTime = 0.05;
    actionIndex = 4;
    shortSleepingAction = false;
    if(sprite.getFillColor() != Color(123,104,238)) 
        sprite.setFillColor(Color(123,104,238));
}

// void Player::moviment() {
//     inMoviment = true;

//     if(Keyboard::isKeyPressed(Keyboard::Right)) {
//         dx = movimentSpeed;
//         // sprite.move(movimentSpeed * gameTime, 0.f);
        
//         frame += FRAME_VELOCITY * gameTime;
//         if(frame > 3) {
//             frame -= 3;
//         }
//         // sprite.setTextureRect(IntRect(PLAYER_SPRITE_WIDHT * (int) frame, 0, PLAYER_SPRITE_WIDHT,PLAYER_SPRITE_HEIGHT));
//     } else if(Keyboard::isKeyPressed(Keyboard::Left)) {
//         dx = -movimentSpeed;
//         // sprite.move(-movimentSpeed * gameTime, 0.f);
//         frame += FRAME_VELOCITY * gameTime;
//         if(frame > 3) {
//             frame -= 3;
//         }
//         // sprite.setTextureRect(IntRect(PLAYER_SPRITE_WIDHT * (int) frame + PLAYER_SPRITE_WIDHT, 0, -PLAYER_SPRITE_WIDHT,PLAYER_SPRITE_HEIGHT));
//     } else {
//         dx = 0;
//         inMoviment = false;
//     }

    
//     sprite.move(dx * gameTime, 0.f);
// }

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
    return actionIndex == 1;
}