//
// Created by 曹先生 on 2021/5/29.
//


#include <ge211.hxx>

#pragma once

struct Game_config
{
    Game_config();

    int obstacle_horizontal_max_velocity;

    int obstacle_vertical_max_velocity;

    int bi_horizontal_max_velocity;

    int bi_vertical_max_velocity;

    int horizontal_wall_thickness;

    int vertical_wall_thickness;

    int vertical_wall_difference;

    int vertical_wall_height;

    int wall_start_x;

    int wall_end_x;

    int scene_width;

    int scene_height;

    int bottom_display_height;

    int bi_radius;

    int obstacle_b_radius;

    float max_car_speed;

    int car_width;

    int car_height;

    int default_car_life;

    int obstacle_a_amount;

    ge211::Dims<int> obstacle_a_body;

    int obstacle_b_amount;

    int lightning_amount;

    float lightning_increment;

    float lightning_time_duration;

    int heart_amount;

    int immunity_amount;

    float immunity_duration;

    int default_acceleration;

    ge211::Posn<int> car_start_position;

    ge211::Posn<int> trophy_top_left;

    ge211::Dims<int> trophy_dims;

    int immunity_while_being_hit;

    ge211::Posn<int> ob_boost_range;
};

