#pragma once

#include "raylib.h"
#include "gamestate.hpp"
#include "statemanager.hpp"
#include "uibutton.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "bird.hpp"
#include "explosion.hpp"
#include "feces.hpp"
#include <vector>

class PlayState : public GameState {

public:
    PlayState(StateManager* manager);
    ~PlayState();

    void render() override;
    void tick(float delta_time) override;
    void handle_input() override;

    void shoot();

    void on_enter() override;
    void on_exit() override;

private:
    StateManager* state_manager;
    UIButton back_button;

    Texture2D spritesheet;
    Texture2D background;

    Player* player;

    std::vector<Bullet> bullets;
    std::vector<Bird> birds;
    std::vector<Explosion> explosions;
    std::vector<Feces> v_feces;

    int bird_amount;

    int defecate_chance;
    bool should_defecate;
    float defecate_cooldown;

    Sound sound_shoot;
    Sound sound_explode;
    Sound sound_defecate;

};
