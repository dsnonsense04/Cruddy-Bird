#pragma once

#include "uibutton.hpp"
#include "gamestate.hpp"
#include "statemanager.hpp"
#include "raylib.h"

class MenuState : public GameState {

public:
    MenuState(StateManager* manager);
    ~MenuState();

    void render() override;
    void tick(float delta_time) override;
    void handle_input() override;

    void on_enter() override;
    void on_exit() override;

private:
    UIButton play_button;
    UIButton exit_button;
    StateManager* state_manager;

    Texture2D background;

};
