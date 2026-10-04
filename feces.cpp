#include "raylib.h"
#include "feces.hpp"

#define SPRITE_SCALE 96

Feces::Feces(Texture2D texture, Vector2 position)
    : texture(texture), position(position), is_on_ground(false)
    {
        this->width = SPRITE_SCALE;
        this->height = SPRITE_SCALE;

        this->dimensions = (Rectangle) {
            this->position.x,
            this->position.y,
            this->width,
            this->height
        };

        this->fall_speed = 250.0f;
    }

void Feces::render() {
    Rectangle feces_falling_source = { 63, 1, 12, 14 };
    Rectangle feces_falling_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };
    Rectangle feces_ground_source = { 63, 16, 12, 14 };
    Rectangle feces_ground_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };

    if (this->position.y < 340) {
        // While feces is falling.
        DrawTexturePro(this->texture, feces_falling_source, feces_falling_dest, { 0, 0 }, 0.0f, WHITE);
    } else if (this->position.y >= 340) {
        // While feces is on the ground.
        DrawTexturePro(this->texture, feces_ground_source, feces_ground_dest, { 0, 0 }, 0.0f, WHITE);
    }
}

void Feces::tick(float delta_time) {
    this->position.y += this->fall_speed * delta_time;

    if (this->position.y >= 340) {
        this->position.y = 340;
        this->is_on_ground = true;
    }

    this->dimensions.x = this->position.x;
    this->dimensions.y = this->position.y;
}

void Feces::set_velocity(Vector2 new_vel) {
    this->velocity = new_vel;
}

Rectangle Feces::get_dimensions() {
    return this->dimensions;
}

Vector2 Feces::get_position() {
    return this->position;
}

Vector2 Feces::get_velocity() {
    return this->velocity;
}

bool Feces::has_touched_ground() {
    return this->is_on_ground;
}
