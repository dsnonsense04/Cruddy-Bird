#include <string>
#include "raylib.h"
#include "uibutton.hpp"

UIButton::UIButton(std::string text, int x, int y, int width, int height)
    : text(text), x(x), y(y), width(width), height(height), has_been_clicked(false)
    {
        this->mouse_pos = GetMousePosition();
        this->dimensions = (Rectangle) {
            this->x,
            this->y,
            this->width,
            this->height
        };
        this->foreground_colour = RAYWHITE;
        this->background_colour = DARKGRAY;
    }

void UIButton::render() {
    // Background rectangle
    DrawRectangle(this->x, this->y, this->width + 25, this->height + 25, this->background_colour);
    // Foreground rectangle
    DrawRectangle(this->x + 5, this->y + 5, this->width + 10, this->height + 10, this->foreground_colour);
    // Foreground text
    DrawText(this->text.c_str(), this->x + 40, this->y + 30, 25, BLACK);
}

void UIButton::handle_input() {
    this->mouse_pos = GetMousePosition();
    Rectangle mouse_dimensions = (Rectangle) {
        this->mouse_pos.x,
        this->mouse_pos.y,
        10,
        10
    };
    if (CheckCollisionRecs(this->dimensions, mouse_dimensions) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        has_been_clicked = true;
    } else {
        has_been_clicked = false;
    }
}

void UIButton::set_text(std::string text) {
    this->text = text;
}

Rectangle UIButton::get_dimensions() {
    return this->dimensions;
}

bool UIButton::is_clicked() {
    return this->has_been_clicked;
}
