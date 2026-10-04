#include "raylib.h"
#include "statemanager.hpp"
#include <memory>

void StateManager::change_state(std::unique_ptr<GameState> new_state) {
    if (current_state)
        current_state->on_exit();
    current_state = std::move(new_state);
    if (current_state)
        current_state->on_enter();
}

void StateManager::handle_input() {
    if (current_state)
        current_state->handle_input();
}

void StateManager::render() {
    if (current_state)
        current_state->render();
}

void StateManager::tick(float delta_time) {
    if (current_state)
        current_state->tick(delta_time);
}
