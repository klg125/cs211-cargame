//
// Created by 曹先生 on 2021/5/29.
//
#pragma once
#include <game_config.hxx>
#include <cmath>
#include "in_motion_objects.hxx"

using Position = ge211::Posn<float>;

struct Car
{
public:
    Car(Game_config config);

    float speed;

    int angle;

    ge211::Dims<float> velocity;

    ge211::Posn<float> top_left;

    ge211::Dims<int> body;

    float max_speed;

    Car
    on_next_frame(double dt);

};

ge211::Posn<int> posn_float_to_int(Position a);
ge211::Posn<int> posn_float_to_int(Position a);
