#pragma once

#include "raylib.h"

class Explosion {

public:
    Explosion(Texture2D texture, Vector2 position);

    void tick(float delta_time);
    void render();

    bool is_finished();

private:
    Texture2D texture;
    Vector2 position;

    float lifetime;

};
