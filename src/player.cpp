#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

// const String PLAYER_TEXTURE = "./assets/sprites/player/idle.png";
const int PLAYER_SPRITE_WIDHT = 50;
const int PLAYER_SPRITE_HEIGHT = 37;
const float FRAME_VELOCITY = 5;

Player::Player(RenderWindow* renderWindow, int groundLocalization) {
    window = renderWindow;
    // texture.loadFromFile(PLAYER_TEXTURE);
    // sprite.setTexture(texture);
    // sprite.setTexture(texture);
    sprite.setSize(Vector2f(100.f, 100.f));
    sprite.setFillColor(Color::White);

    frame = 0.f;
    gameTime = 0.0f;
    movimentSpeed = 300.f;
    dx = 0;
    dy = 0;
    onGround = true;
    inMoviment = false;
    inJump = false;
    inFall = false;

    this->groundPosition = groundLocalization - sprite.getGlobalBounds().height;
    // sprite.setTextureRect(IntRect(0, groundPosition, PLAYER_SPRITE_WIDHT, PLAYER_SPRITE_HEIGHT));
    setPosition(Vector2f((window->getSize().x/2) - sprite.getGlobalBounds().width - 50 , groundPosition));


}

void Player::updateGameTime(float clock) {
    gameTime = clock;
}

void Player::setPosition(Vector2f position) {
    sprite.setPosition(position);
}

void Player::render() {
    window->draw(sprite);
}

void Player::moviment() {
    inMoviment = true;

    if(Keyboard::isKeyPressed(Keyboard::Right)) {
        dx = movimentSpeed;
        // sprite.move(movimentSpeed * gameTime, 0.f);
        
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(PLAYER_SPRITE_WIDHT * (int) frame, 0, PLAYER_SPRITE_WIDHT,PLAYER_SPRITE_HEIGHT));
    } else if(Keyboard::isKeyPressed(Keyboard::Left)) {
        dx = -movimentSpeed;
        // sprite.move(-movimentSpeed * gameTime, 0.f);
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(PLAYER_SPRITE_WIDHT * (int) frame + PLAYER_SPRITE_WIDHT, 0, -PLAYER_SPRITE_WIDHT,PLAYER_SPRITE_HEIGHT));
    } else {
        dx = 0;
        inMoviment = false;
    }

    
    sprite.move(dx * gameTime, 0.f);
}

void Player::idle() {
    inMoviment = true;
    int movimentControl = 1;

    if(dx >= 0) {
        
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(PLAYER_SPRITE_WIDHT * (int) frame, 0, PLAYER_SPRITE_WIDHT,PLAYER_SPRITE_HEIGHT));
    } else  {
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(PLAYER_SPRITE_WIDHT * (int) frame + PLAYER_SPRITE_WIDHT, 0, -PLAYER_SPRITE_WIDHT,PLAYER_SPRITE_HEIGHT));
    }

    if(!inMoviment) {
        movimentControl = 0;
    }
    
    sprite.move(dx * gameTime * movimentControl, 0.f);
}

void Player::update() {
    moviment();
    idle();
}