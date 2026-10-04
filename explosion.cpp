#include "raylib.h"
#include "explosion.hpp"

#define SPRITE_SCALE 96

Explosion::Explosion(Texture2D texture, Vector2 position)
    : texture(texture), position(position)
    {
        this->lifetime = 0.5f;
    }

void Explosion::tick(float delta_time) {
    this->lifetime -= delta_time;
}

void Explosion::render() {
    Rectangle explosion_source = { 48, 16, 12, 14 };
    Rectangle explosion_destination = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };
    DrawTexturePro(this->texture, explosion_source, explosion_destination, { 0, 0 }, 0.0f, WHITE);
}

bool Explosion::is_finished() {
    return this->lifetime <= 0.0f;
}
