#pragma once

#include "raylib.h"

class Feces {

public:
    Feces(Texture2D texture, Vector2 position);

    void tick(float delta_time);
    void render();

    void set_velocity(Vector2 new_vel);
    bool has_touched_ground();

    Rectangle get_dimensions();
    Vector2 get_position();
    Vector2 get_velocity();

private:
    Texture2D texture;
    Vector2 position;
    Vector2 velocity;
    int width; int height;
    float fall_speed;

    bool is_on_ground;

    Rectangle dimensions;

};
