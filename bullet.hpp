#pragma once

#include "raylib.h"

class Bullet {

public:
    Bullet(Texture2D texture, Vector2 position);

    void tick(float delta_time);
    void render();
    void destroy();

    bool is_off_screen();
    bool is_dead();

    Rectangle get_dimensions();
    Vector2 get_position();

private:
    Vector2 position;
    Rectangle dimensions;
    float move_speed;

    bool dead;

    int width;
    int height;

    Texture2D texture;

};
