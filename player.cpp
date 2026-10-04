#include "player.hpp"
#include "raylib.h"

#define SPRITE_SCALE 96
#define Y_LEVEL 340

Player::Player(Texture2D texture, int x, int y)
    : texture(texture), x(x), y(y)
    {
        this->width = SPRITE_SCALE;
        this->height = SPRITE_SCALE;

        this->position = { this->x, this->y };
        this->dimensions = (Rectangle) {
            this->position.x,
            this->position.y,
            this->width,
            this->height
        };

        this->move_speed = 150.0f;
        this->health = 100.0f;
        this->damage_dealt = 25.0f;
    }

void Player::render() {
    Rectangle player_right_source = { 1, 1, 14, 14 };
    Rectangle player_left_source = { 1, 16, 14, 14 };
    Rectangle player_idle_source = {1, 31, 14, 14 };
    Rectangle player_right_dest = { this->position.x, Y_LEVEL, SPRITE_SCALE, SPRITE_SCALE };
    Rectangle player_left_dest = { this->position.x, Y_LEVEL, SPRITE_SCALE, SPRITE_SCALE };
    Rectangle player_idle_dest = { this->position.x, Y_LEVEL, SPRITE_SCALE, SPRITE_SCALE };

    if (IsKeyDown(KEY_D)) {
        this->position.x += this->move_speed * GetFrameTime();
        DrawTexturePro(this->texture, player_right_source, player_right_dest, {0, 0}, 0.0f, WHITE);
    } else if (IsKeyDown(KEY_A)) {
        this->position.x -= this->move_speed * GetFrameTime();
        DrawTexturePro(this->texture, player_left_source, player_left_dest, {0, 0}, 0.0f, WHITE);
    } else {
        DrawTexturePro(this->texture, player_idle_source, player_idle_dest, {0, 0}, 0.0f, WHITE);
    }

    DrawRectangle(640 / 2 - 100, 440, 200, 30, RED);
    DrawRectangle(640 / 2 - 100, 440, this->health * 2, 30, GREEN);
}

void Player::tick(float delta_time) {
    if (this->position.x <= 0)
        this->position.x = 0;
    else if (this->position.x >= 640 - 96)
        this->position.x = 640 - 96;

    this->dimensions.x = this->position.x;
    this->dimensions.y = this->position.y;
}

void Player::set_position(Vector2 new_pos) {
    this->position = new_pos;
}

void Player::set_health(float new_health) {
    this->health = new_health;
}

Rectangle Player::get_dimensions() {
    return this->dimensions;
}

Vector2 Player::get_position() {
    return this->position;
}

float Player::get_move_speed() {
    return this->move_speed;
}

float Player::get_health() {
    return this->health;
}

float Player::get_damage_dealt() {
    return this->damage_dealt;
}
