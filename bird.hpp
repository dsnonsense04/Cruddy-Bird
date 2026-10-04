#pragma once

enum class BirdSpecies {

    Cardinal,
    BlueJay,
    Duck

};

enum class BirdDirection {

    Left,
    Right

};

class Bird {

public:
    Bird(Texture2D texture, BirdSpecies bird_species, int x, int y);

    void render();
    void tick(float delta_time);
    void set_speed(float new_speed);

    void destroy();

    bool is_dead();

    Rectangle get_dimensions();
    Vector2 get_position();
    Vector2 get_velocity();
    float get_move_speed();

private:
    Rectangle dimensions;
    int x; int y;
    int width; int height;

    bool dead;

    Vector2 position;
    Vector2 velocity;
    float move_speed;

    Texture2D texture;
    BirdSpecies bird_species;
    BirdDirection bird_direction;

};
