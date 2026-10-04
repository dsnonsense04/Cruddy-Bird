#include "menustate.hpp"
#include "playstate.hpp"
#include "statemanager.hpp"
#include "uibutton.hpp"

MenuState::MenuState(StateManager* manager)
    : play_button("Play", 640 / 2 - 100, 480 / 2, 100, 50),
      exit_button("Quit", 640 / 2 - 100, 480 / 2 + 100, 100, 50),
      state_manager(manager)
{
    this->background = LoadTexture("assets/textures/MC_Dirt_Background.png");
    SetTextureFilter(this->background, TEXTURE_FILTER_POINT);
}

MenuState::~MenuState() {
    UnloadTexture(this->background);
}

void MenuState::handle_input() {
    play_button.handle_input();
    exit_button.handle_input();

    if (exit_button.is_clicked()) {
        CloseWindow();
        exit(EXIT_SUCCESS);
    }

    if (play_button.is_clicked()) {
        state_manager->change_state(std::make_unique<PlayState>(state_manager));
    }
}

void MenuState::render() {
    Rectangle background_source = { 0, 0, 900, 900 };
    Rectangle background_scaling = { 0, 0, 640, 480 };
    DrawTexturePro(this->background, background_source, background_scaling, { 0, 0 }, 0.0f, WHITE);
    DrawText("Cruddy Bird", 640 / 2 - 170, 100, 50, RAYWHITE);
    play_button.render();
    exit_button.render();
}

void MenuState::tick(float delta_time) {
}

void MenuState::on_exit() {
}

void MenuState::on_enter() {
}
