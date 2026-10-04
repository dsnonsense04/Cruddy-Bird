#pragma once

#include <memory>
#include "gamestate.hpp"

class StateManager {

    public:
        void change_state(std::unique_ptr<GameState> new_state);

        void handle_input();
        void tick(float delta_time);
        void render();

    private:
        std::unique_ptr<GameState> current_state;

};
