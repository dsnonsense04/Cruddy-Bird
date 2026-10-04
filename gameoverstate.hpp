#pragma once

#include "raylib.h"
#include "gamestate.hpp"
#include "uibutton.hpp"
#include "statemanager.hpp"

class GameOverState : public GameState {

public:
    GameOverState(StateManager* manager);
    ~GameOverState();

    void tick(float delta_time) override;
    void render() override;
    void handle_input() override;

    void on_enter() override;
    void on_exit() override;

private:
    StateManager* state_manager;
    UIButton exit_button;

    Texture2D background;
};
