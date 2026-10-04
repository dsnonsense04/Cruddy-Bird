#include "raylib.h"
#include "bird.hpp"

#define SPRITE_SCALE 96

Bird::Bird(Texture2D texture, BirdSpecies bird_species, int x, int y)
    : texture(texture), bird_species(bird_species), x(x), y(y), dead(false)
    {
        this->position.x = this->x;
        this->position.y = this->y;
        this->width = SPRITE_SCALE;
        this->height = SPRITE_SCALE;

        this->move_speed = 250.0f;

        this->dimensions = (Rectangle) {
            this->position.x,
            this->position.y,
            this->width,
            this->height
        };

        if (GetRandomValue(0, 1) == 0) {
            this->bird_direction = BirdDirection::Left;
        } else {
            this->bird_direction= BirdDirection::Right;
        }
    }

void Bird::tick(float delta_time) {
    if (this->bird_direction == BirdDirection::Left) {
        this->position.x -= this->move_speed * delta_time;
        if (this->position.x <= -SPRITE_SCALE)
            this->position.x = 640 + SPRITE_SCALE;
    } else {
        this->position.x += this->move_speed * delta_time;
        if (this->position.x > 640 + SPRITE_SCALE)
            this->position.x = -SPRITE_SCALE;
    }

    this->dimensions.x = this->position.x;
    this->dimensions.y = this->position.y;
}

void Bird::render() {
    if (this->bird_direction == BirdDirection::Left) {
        Rectangle LFS_blue_jay = { 16, 1, 14, 14 };
        Rectangle LFS_cardinal = { 16, 16, 14, 14 };
        Rectangle LFS_duck = { 16, 32, 14, 12 };

        Rectangle LFS_blue_jay_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };
        Rectangle LFS_cardinal_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };
        Rectangle LFS_duck_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };

        switch (this->bird_species) {
            case BirdSpecies::BlueJay:
                // Render left-facing BlueJay.
                DrawTexturePro(this->texture, LFS_blue_jay, LFS_blue_jay_dest, { 0, 0 }, 0.0f, WHITE);
                break;
            case BirdSpecies::Cardinal:
                // Render left-facing Cardinal.
                DrawTexturePro(this->texture, LFS_cardinal, LFS_cardinal_dest, { 0, 0 }, 0.0f, WHITE);
                break;
            case BirdSpecies::Duck:
                // Render left-facing Duck.
                DrawTexturePro(this->texture, LFS_duck, LFS_duck_dest, { 0, 0 }, 0.0f, WHITE);
                break;
        }
    } else {
        Rectangle RFS_blue_jay = { 32, 1, 12, 14 };
        Rectangle RFS_cardinal = { 32, 16, 12, 14 };
        Rectangle RFS_duck = { 32, 32, 12, 12 };

        Rectangle RFS_blue_jay_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };
        Rectangle RFS_cardinal_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };
        Rectangle RFS_duck_dest = { this->position.x, this->position.y, SPRITE_SCALE, SPRITE_SCALE };

        switch (this->bird_species) {
            case BirdSpecies::BlueJay:
                // Render right-facing BlueJay.
                DrawTexturePro(this->texture, RFS_blue_jay, RFS_blue_jay_dest, { 0, 0 }, 0.0f, WHITE);
                break;
            case BirdSpecies::Cardinal:
                // Render right-facing Cardinal.
                DrawTexturePro(this->texture, RFS_cardinal, RFS_cardinal_dest, { 0, 0 }, 0.0f, WHITE);
                break;
            case BirdSpecies::Duck:
                // Render right-facing Duck.
                DrawTexturePro(this->texture, RFS_duck, RFS_duck_dest, { 0, 0 }, 0.0f, WHITE);
                break;
        }
    }
}

void Bird::destroy() {
    this->dead = true;
}

void Bird::set_speed(float new_speed) {
    this->move_speed = new_speed;
}

bool Bird::is_dead() {
    return this->dead;
}

Rectangle Bird::get_dimensions() {
    return this->dimensions;
}

Vector2 Bird::get_position() {
    return this->position;
}

Vector2 Bird::get_velocity() {
    return this->velocity;
}
