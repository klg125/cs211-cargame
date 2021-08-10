//
// Created by 曹先生 on 2021/5/31.
//

#include "game_config.hxx"

Game_config::Game_config()
        : obstacle_horizontal_max_velocity(100),
          obstacle_vertical_max_velocity(100),
          bi_horizontal_max_velocity(100),
          bi_vertical_max_velocity(100),
          horizontal_wall_thickness(50),
          vertical_wall_thickness(20),
          vertical_wall_difference(200),
          vertical_wall_height(500),
          wall_start_x(100),
          wall_end_x(900),
          scene_width(1200),
          scene_height(800),
          bottom_display_height(0),
          bi_radius(10),
          obstacle_b_radius(10),
          max_car_speed(6),
          car_width(20),
          car_height(20),
          default_car_life(1),
          obstacle_a_amount(5),
          obstacle_a_body({10,10}),
          obstacle_b_amount(5),
          lightning_amount(2),
          lightning_increment(5),
          lightning_time_duration(10),
          heart_amount(2),
          immunity_amount(2),
          immunity_duration(10),
          immunity_while_being_hit(1),
          default_acceleration(5),
          car_start_position(ge211::Posn<int> {100,600}),
          trophy_top_left(ge211::Posn<int> {800, 480}),
          trophy_dims({20,30}),
          ob_boost_range(ge211::Posn<int> {-1,3})
{

}