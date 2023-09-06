#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

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
    attackingAction =false;
    blockingAction =false;


}

void Player::updateGameTime(float clock) {
    gameTime = clock;
}

void Player::setPosition(Vector2f position) {
    sprite.setPosition(position);
}

void Player::render() {
    window->draw(sprite);
    window->draw(attackBox);
    lifeBar->render();
}

void Player::update(float clock) {
    updateGameTime(clock);
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
    if(timerActionTransition >= actiontransitionTime) {
        timerActionTransition = 0;
    }
    if(timerActionTransition == 0) {
        if(Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            attack();
        } else if(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            block();
        } else {
            idle();
        }
    }
}

void Player::idle() {
    actionIndex = 0;
    if(sprite.getFillColor() != Color::White)
        sprite.setFillColor(Color::White);
}
void Player::block() {
    actionIndex = 1;
    blockingAction = true;
    if(sprite.getFillColor() != Color::Blue)
        sprite.setFillColor(Color::Blue);
}
void Player::attack() {
    actionIndex = 2;
    attackingAction = true;
    if(sprite.getFillColor() != Color::Red)
        sprite.setFillColor(Color::Red);
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
        lifeBar->takeDamage(valueDamage);
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
};
bool Player::inBlocking() {
    return actionIndex == 1;
};