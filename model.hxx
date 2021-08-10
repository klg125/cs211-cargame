#pragma once

#include <ge211.hxx>
#include <car.hxx>
#include <in_motion_objects.hxx>

class Model
{
public:
    explicit Model(Game_config const& config = Game_config());

    Game_config conf;
    Car car;

    std::vector<in_motion_object> lightning_list;
    std::vector<in_motion_object> heart_list;
    std::vector<in_motion_object> immunity_list;
    std::vector<in_motion_object> obstacle_b_list;
    std::vector<ge211::Rect<int>> wall_list;
    std::vector<ge211::Rect<int>> obstacle_a_list;
    std::vector<int> axis;

    bool immunity;
    bool lightning;
    int life;

    float immunity_time;
    float lightning_time;

    void
    print_model_all();

    void
    print_stationary_objects_in_model();
    void
    print_moving_objects_in_model();
    void
    on_frame(double dt);
    bool game_end;
    bool game_win;
};

Car car_on_next_frame(double dt);

void imo_list_on_frame(std::vector<in_motion_object>&imo_list,std::vector<
        ge211::Rect<int>>& rect_list,double dt);

void print_rect(ge211::Rect<int> rect);

