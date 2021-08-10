//
// Created by 曹先生 on 2021/5/30.
//

#pragma once
#include <ge211.hxx>

#ifndef GAME_IN_MOTION_OBJECTS_HXX
#define GAME_IN_MOTION_OBJECTS_HXX

struct in_motion_object
{
    in_motion_object(
            ge211::Dims<float> v,
            ge211::Posn<float> c,
            int r);
public:
    ge211::Dims<float> velocity;
    ge211::Posn<float> center;
    int radius;

    in_motion_object
    next(double dt) const;

    void
    print_imo();
    void
    reflect_vertical();
    void
    reflect_horizontal();
    ge211::Posn<float>
    top_left() const;
    bool
    hits_block(ge211::Rect<int> block);
    bool
    hits_block(ge211::Rect<float> block);
    std::vector<int>
    collided_side(ge211::Rect<int> block);
};

void print_imo_list(std::vector<in_motion_object> list);

in_motion_object imo_generator(int hv_low,int hv_up,int vv_low, int vv_up,
                               int x_low, int x_up, int y_low, int y_up,
                               int r);

#endif //GAME_IN_MOTION_OBJECTS_HXX
