#include "enemy.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

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
    sprite.setFillColor(Color::Blue);

    frame = 0.f;
    gameTime = 0.0f;
    movimentSpeed = 300.f;
    dx = 0;
    dy = 0;
    attackDistance = 50;
    onGround = true;
    inMoviment = false;
    inJump = false;
    inFall = false;

    this->groundPosition = groundLocalization - sprite.getGlobalBounds().height;
    // sprite.setTextureRect(IntRect(0, groundPosition, ENEMY_SPRITE_WIDHT, ENEMY_SPRITE_HEIGHT));
    setPosition(Vector2f(0.f, groundPosition));


}

void Enemy::updateGameTime(float clock) {
    gameTime = clock;
}

void Enemy::setPosition(Vector2f position) {
    sprite.setPosition(position);
}

void Enemy::render() {
    window->draw(sprite);
}

void Enemy::moviment() {
    inMoviment = true;

    if((player->sprite.getPosition().x - attackDistance) > (sprite.getPosition().x + sprite.getGlobalBounds().width)) {
        dx = movimentSpeed;
        // sprite.move(movimentSpeed * gameTime, 0.f);
        
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(ENEMY_SPRITE_WIDHT * (int) frame, 0, ENEMY_SPRITE_WIDHT,ENEMY_SPRITE_HEIGHT));
    } else if((player->sprite.getPosition().x + attackDistance + player->sprite.getGlobalBounds().width) < sprite.getPosition().x) {
        dx = -movimentSpeed;
        // sprite.move(-movimentSpeed * gameTime, 0.f);
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(ENEMY_SPRITE_WIDHT * (int) frame + ENEMY_SPRITE_WIDHT, 0, -ENEMY_SPRITE_WIDHT,ENEMY_SPRITE_HEIGHT));
    } else {
        dx = 0;
        inMoviment = false;
    }

    
    sprite.move(dx * gameTime, 0.f);
}

void Enemy::idle() {
    inMoviment = true;
    int movimentControl = 1;

    if(dx >= 0) {
        
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(ENEMY_SPRITE_WIDHT * (int) frame, 0, ENEMY_SPRITE_WIDHT,ENEMY_SPRITE_HEIGHT));
    } else  {
        frame += FRAME_VELOCITY * gameTime;
        if(frame > 3) {
            frame -= 3;
        }
        // sprite.setTextureRect(IntRect(ENEMY_SPRITE_WIDHT * (int) frame + ENEMY_SPRITE_WIDHT, 0, -ENEMY_SPRITE_WIDHT,ENEMY_SPRITE_HEIGHT));
    }

    if(!inMoviment) {
        movimentControl = 0;
    }
    
    sprite.move(dx * gameTime * movimentControl, 0.f);
}

void Enemy::update() {
    moviment();
    idle();
}