#include "bullet.hpp"
#include "raylib.h"

#define SPRITE_SCALE 96

Bullet::Bullet(Texture2D texture, Vector2 position)
    : texture(texture), position(position), dead(false)
    {
        this->width = SPRITE_SCALE / 2;
        this->height = SPRITE_SCALE / 2;

        this->dimensions = (Rectangle) {
            this->position.x,
            this->position.y,
            this->width,
            this->height
        };

        this->move_speed = 500.0f;
    }

void Bullet::render() {
    Rectangle bullet_source = { 48, 1, 12, 14 };
    Rectangle bullet_dest = { this->position.x, this->position.y, SPRITE_SCALE / 2, SPRITE_SCALE / 2 };
    DrawTexturePro(this->texture, bullet_source, bullet_dest, {0, 0}, 0.0f, WHITE);
}

void Bullet::tick(float delta_time) {
    this->position.y -= this->move_speed * delta_time;

    this->dimensions.x = this->position.x;
    this->dimensions.y = this->position.y;
}

void Bullet::destroy() {
    this->dead = true;
}

bool Bullet::is_off_screen() {
    return this->position.y + this->height < 0;
}

bool Bullet::is_dead() {
    return this->dead;
}

Rectangle Bullet::get_dimensions() {
    return this->dimensions;
}
