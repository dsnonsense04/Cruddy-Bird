#pragma once

#include "raylib.h"
#include <string>

class UIButton {

public:
    UIButton(std::string text, int x, int y, int width, int height);

    // Ran once every frame
    void render();
    void handle_input();

    void set_text(std::string text);

    Rectangle get_dimensions();
    bool is_clicked();

private:
    Rectangle dimensions;
    int x; int y;
    int width; int height;

    Color foreground_colour;
    Color background_colour;

    Vector2 mouse_pos;
    bool has_been_clicked;
    std::string text;

};
