#pragma once

#include "model.hxx"

struct View
{
public:
    explicit View(Model&);

    void draw(ge211::Sprite_set& sprites);

    Model& model_;

    ge211::Circle_sprite heart_sprite;
    ge211::Circle_sprite immunity_sprite;
    ge211::Circle_sprite lightning_sprite;
    ge211::Circle_sprite obstacle_b_sprite;
    ge211::Rectangle_sprite obstacle_a_sprite;
    ge211::Rectangle_sprite trophy_sprite;
    ge211::Image_sprite const car_sprite_image;
    ge211::Image_sprite const trophy_image;
    ge211::Image_sprite lives;
    ge211::Image_sprite lightning_image;
    ge211::Image_sprite immunity_image;
    ge211::Rectangle_sprite car_sprite;
    std::vector<ge211::Rectangle_sprite> wall_list;
    std::vector<ge211::Posn<int>> wall_top_left_list;
    ge211::Font const help_font_;
    ge211::Text_sprite lost_message;
    ge211::Text_sprite win_message;

};
