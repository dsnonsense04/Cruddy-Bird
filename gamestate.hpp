#pragma once

class GameState {

public:
    virtual ~GameState() = default;

    virtual void tick(float delta_time) = 0;
    virtual void render() = 0;
    virtual void handle_input() = 0;

    virtual void on_enter() {}
    virtual void on_exit() {}

};
