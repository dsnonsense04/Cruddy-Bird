#pragma once

#include "raylib.h"

class Player {

public:
    Player(Texture2D texture, int x, int y);

    void render();
    void tick(float delta_time);

    void set_health(float new_health);
    void set_position(Vector2 new_pos);

    Rectangle get_dimensions();
    Vector2 get_position();

    float get_move_speed();
    float get_health();
    float get_damage_dealt();


private:
    Rectangle dimensions;
    Rectangle health_rect_red;
    Rectangle health_rect_green;
    Rectangle health_rect_bg;

    int x; int y;
    int width; int height;

    float move_speed;
    float health;
    float damage_dealt;

    Vector2 position;

    Texture2D texture;

};
