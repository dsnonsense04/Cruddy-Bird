#include "raylib.h"
#include "gameoverstate.hpp"
#include "uibutton.hpp"
#include "menustate.hpp"

GameOverState::GameOverState(StateManager* manager)
    : exit_button("Menu", 640 / 2 - 100, 480 / 2, 100, 50),
      state_manager(manager)
      {
            this->background = LoadTexture("assets/textures/MC_Dirt_Background.png");
            SetTextureFilter(this->background, TEXTURE_FILTER_POINT);
      }

GameOverState::~GameOverState() {
    UnloadTexture(this->background);
}

void GameOverState::render() {
    Rectangle background_source = { 0, 0, 900, 900 };
    Rectangle background_scaling = { 0, 0, 640, 480 };
    DrawTexturePro(this->background, background_source, background_scaling, { 0, 0 }, 0.0f, WHITE);
    DrawText("Game over! You died.", 640 / 2 - 200, 480 / 2 - 100, 32, RAYWHITE);
    exit_button.render();
}

void GameOverState::handle_input() {
    exit_button.handle_input();
    if (exit_button.is_clicked()) {
        state_manager->change_state(std::make_unique<MenuState>(state_manager));
    }
}

void GameOverState::tick(float delta_time) {
}

void GameOverState::on_enter() {
}

void GameOverState::on_exit() {
}
