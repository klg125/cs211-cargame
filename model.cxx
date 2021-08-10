#include "model.hxx"

Model::Model(Game_config const& config)
        : conf(config),
          car(Car(config)),
          immunity(false),
          lightning(false),
          life(config.default_car_life),
          game_end(false),
          game_win(false)
{
    ge211::Rect<int>
            top_wall
            (0, 0, config.scene_width, config.horizontal_wall_thickness);

    ge211::Rect<int>
            bottom_wall
            (0,
             config.scene_height - config.horizontal_wall_thickness,
             config.scene_width,
             config.horizontal_wall_thickness);

    wall_list.push_back(top_wall);
    wall_list.push_back(bottom_wall);

    ge211::Rect<int>
            vertical_wall(config.wall_start_x,
                          config.horizontal_wall_thickness,
                          config.vertical_wall_thickness,
                          config.vertical_wall_height);

    wall_list.push_back(vertical_wall);

    int count = 0;
    int
            y_two =
            config.scene_height - config.vertical_wall_height -
            config.horizontal_wall_thickness;

    while (vertical_wall.x + config.vertical_wall_difference +
           2 * config.vertical_wall_thickness <= config.wall_end_x) {
        vertical_wall.x += config.vertical_wall_difference;
        if (count % 2 == 0) {
            vertical_wall.y = config.horizontal_wall_thickness;
            wall_list.push_back(vertical_wall);
        } else {
            vertical_wall.y = y_two;
            wall_list.push_back(vertical_wall);
        }
        count++;
    }


    for (int i = 2; i < wall_list.size(); i++) {
        ge211::Rect<int> rect = wall_list[i];
        int adder = static_cast <int>(config.vertical_wall_difference / 2);
        axis.push_back(
                rect.x + adder);
    }

    ge211::Random_source<int>
            axis_generator(0, axis.size() - 1);

/*    int ohmv = config.obstacle_horizontal_max_velocity;
    int bhmv = config.bi_horizontal_max_velocity;
    int ovmv = config.obstacle_vertical_max_velocity;
    int bvmv = config.bi_vertical_max_velocity;*/

    for (int i = 0; i < config.heart_amount; i++) {
        int x = axis[axis_generator.next()];
        heart_list.push_back(
                imo_generator(61,
                              120,
                              61,
                              120,
                              x,
                              x,
                              config.horizontal_wall_thickness,
                              config.scene_height -
                              config.horizontal_wall_thickness,
                              config.bi_radius));
    }

    for (int i = 0; i < config.lightning_amount; i++) {
        int x = axis[axis_generator.next()];
        lightning_list.push_back(
                imo_generator(61,
                              120,
                              61,
                              120,
                              x,
                              x,
                              config.horizontal_wall_thickness,
                              config.scene_height -
                              config.horizontal_wall_thickness,
                              config.bi_radius));
    }

    for (int i = 0; i < config.immunity_amount; i++) {
        int x = axis[axis_generator.next()];
        immunity_list.push_back(
                imo_generator(61,
                              120,
                              61,
                              120,
                              x,
                              x,
                              config.horizontal_wall_thickness,
                              config.scene_height -
                              config.horizontal_wall_thickness,
                              config.bi_radius));
    }

    for (int i = 0; i < config.obstacle_a_amount; i++) {
        ge211::Rect<int> rect;
        int x;
        ge211::Random_source<int> distance_from_axis(
                0,
                config.vertical_wall_difference /
                2 -
                config.obstacle_a_body
                      .width);

        ge211::Random_source<int> y(config.horizontal_wall_thickness +
                                    2 * config.obstacle_a_body.width,
                                    config.scene_height -
                                    config.horizontal_wall_thickness -
                                    2 * config.obstacle_a_body.width);

        x = axis[axis_generator.next()];
        rect.x = x + distance_from_axis.next();
        rect.y = y.next();
        rect.width = config.obstacle_a_body.width;
        rect.height = config.obstacle_a_body.height;
        obstacle_a_list.push_back(rect);
    }

    for (int i = 0; i < config.obstacle_b_amount; i++) {
        int x = axis[axis_generator.next()];
        obstacle_b_list.push_back(
                imo_generator(61,
                              120,
                              61,
                              120,
                              x,
                              x,
                              config.horizontal_wall_thickness,
                              config.scene_height -
                              config.horizontal_wall_thickness,
                              config.obstacle_b_radius));
    }
}

void
print_rect(ge211::Rect<int> rect)
{
    printf("printing rectangle... \n");
    printf("Top left: x = %d   y = %d \n", rect.x, rect.y);
    printf("Dimensions: width = %d   height = %d \n", rect.width, rect.height);
}

void
print_rect_list(std::vector<ge211::Rect<int>> list)
{
    for (ge211::Rect<int> i: list) {
        print_rect(i);
    }
}

bool rect_collision(ge211::Rect<int> rect1, ge211::Rect<float> rect2)
{
    if (rect1.x < rect2.x + rect2.width &&
        rect1.x + rect1.width > rect2.x &&
        rect1.y < rect2.y + rect2.height &&
        rect1.y + rect1.height > rect2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void
Model::print_stationary_objects_in_model()
{

    printf("printing wall_list... \n");
    print_rect_list(wall_list);
    printf("\n\n\nprinting axis... \n");
    for (int i: axis) {
        printf("%d,", i);
    }
    printf("\n\n\n");
}

void
Model::print_moving_objects_in_model()
{
    printf("printing heart_list... \n");
    print_imo_list(heart_list);
    printf("printing lightning_list... \n");
    print_imo_list(lightning_list);
    printf("printing immunity_list... \n");
    print_imo_list(immunity_list);
    printf("\n\n\nprinting obstacle a... \n");
    print_rect_list(obstacle_a_list);
    printf("printing obstacle b... \n");
    print_imo_list(obstacle_b_list);
}

void
Model::print_model_all()
{
    print_moving_objects_in_model();
    print_stationary_objects_in_model();
}

bool
normal_consistent(int a, float v)
{
    if (a == 0) {
        return false;
    }

    if (a == -1) {
        if (v < 0) {
            return false;
        }
    } else if (a == 1) {
        if (v > 0) {
            return false;
        }
    }
    return true;
}

void
imo_on_frame(
        in_motion_object& imo_in, std::vector<
        ge211::Rect<int>>& rect_list, double dt)
{
    in_motion_object imo = imo_in.next(dt);
    for (int i = 0; i < rect_list.size(); i++) {
        if (imo.hits_block(rect_list[i])) {
            std::vector<int> hit_side = imo.collided_side(rect_list[i]);
            if (hit_side[0] != 0 && normal_consistent(hit_side[0], imo.velocity
                                                                      .width)) {
                imo_in.reflect_horizontal();
            }
            if (hit_side[1] != 0 && normal_consistent(hit_side[1], imo.velocity
                                                                      .height)) {
                imo_in.reflect_vertical();
            }
        }
    }
}

std::vector<in_motion_object>
imo_list_next(
        std::vector<in_motion_object> list, double dt)
{
    std::vector<in_motion_object> return_list;
    for (in_motion_object i: list) {
        return_list.push_back(i.next(dt));
    }
    return return_list;
}

void
imo_list_on_frame(
        std::vector<in_motion_object>& imo_list, std::vector<
        ge211::Rect<int>>& rect_list, double dt)
{
    for (int i = 0; i < imo_list.size(); i++) {
        in_motion_object b = imo_list[i];
        imo_on_frame(imo_list[i], rect_list, dt);
        imo_list[i] = imo_list[i].next(dt);
    }
}

void
imo_on_frame_ob(
        in_motion_object& imo_in, std::vector<
        ge211::Rect<int>>& rect_list, double dt,ge211::Posn<int> range)
{
    in_motion_object imo = imo_in.next(dt);
    for (int i = 0; i < rect_list.size(); i++) {
        if (imo.hits_block(rect_list[i])) {
            ge211::Random_source<int> a(range.x,range.y);
            std::vector<int> hit_side = imo.collided_side(rect_list[i]);
            if (hit_side[0] != 0 && normal_consistent(hit_side[0], imo.velocity
                                                                      .width)) {
                imo_in.reflect_horizontal();
                imo_in.velocity.width+=a.next();
            }
            if (hit_side[1] != 0 && normal_consistent(hit_side[1], imo.velocity
                                                                      .height)) {
                imo_in.reflect_vertical();
                imo_in.velocity.height+=a.next();
            }
        }
    }
}

void
imo_list_on_frame_ob(
        std::vector<in_motion_object>& imo_list, std::vector<
        ge211::Rect<int>>& rect_list, double dt,ge211::Posn<int> range)
{
    for (int i = 0; i < imo_list.size(); i++) {
        in_motion_object b = imo_list[i];
        imo_on_frame_ob(imo_list[i], rect_list, dt,range);
        imo_list[i] = imo_list[i].next(dt);
    }
}

ge211::Dims<float> lightning_velocity(ge211::Dims<float> v,float increment,
                                      int angle)
{
    ge211::Dims<float> return_v=v;
    if(angle==0)
    {
        return_v.width += increment;
    }
    else if(angle==1)
    {
        return_v.height += increment;
    }
    else if(angle==2)
    {
        return_v.width -= increment;
    }
    else
    {
        return_v.height -= increment;
    }
    return return_v;
}

void
Model::on_frame(double dt)
{
    if (life == 0) {
        game_end = true;
        game_win = false;
    }

    if (lightning) {
        car.max_speed = conf.max_car_speed + conf.lightning_increment;
        if ((lightning_time -= dt) < 0) {
            lightning_time = 0;
        } else {
            lightning_time -= dt;
        }
    }

    car = car.on_next_frame(dt);

    ge211::Rect<float> bo(car.top_left.x, car.top_left.y, car.body.width,
                          car.body.height);

    ge211::Rect<int> trophy(conf.trophy_top_left.x, conf.trophy_top_left.y,
                            conf.trophy_dims.width, conf.trophy_dims.height);

    if (rect_collision(trophy, bo)) {
        game_end = true;
        game_win = true;
    }

    if(!game_end)
    {
        std::vector<in_motion_object> imo_list_n = imo_list_next(
                heart_list, dt);

        for (ge211::Rect<int> i : wall_list) {
            if (rect_collision(i, bo)) {
                life = 0;
            }
        }

        for (int i = 0; i < imo_list_n.size(); i++) {
            ge211::Rect<float> car_rect(car.top_left.x,
                                        car.top_left.y,
                                        car.body
                                           .width,
                                        car.body.height);
            if (imo_list_n[i].hits_block(car_rect)) {
                life += 1;
                heart_list[i] = heart_list[heart_list.size() - 1];
                heart_list.pop_back();
            }
        }

        imo_list_n = imo_list_next(lightning_list, dt);

        for (int i = 0; i < imo_list_n.size(); i++) {
            ge211::Rect<float> car_rect(car.top_left.x,
                                        car.top_left.y,
                                        car.body
                                           .width,
                                        car.body.height);
            if (imo_list_n[i].hits_block(car_rect)) {
                lightning_time += conf.lightning_time_duration;
                lightning_list[i] = lightning_list[lightning_list.size() - 1];
                lightning_list.pop_back();
            }
        }

        imo_list_n = imo_list_next(immunity_list, dt);

        for (int i = 0; i < imo_list_n.size(); i++) {
            ge211::Rect<float> car_rect(car.top_left.x,
                                        car.top_left.y,
                                        car.body
                                           .width,
                                        car.body.height);
            if (imo_list_n[i].hits_block(car_rect)) {
                immunity_time += conf.immunity_duration;
                immunity_list[i] = immunity_list[immunity_list.size() - 1];
                immunity_list.pop_back();
            }
        }

        if (immunity_time > 0) {
            immunity = true;
        } else {
            immunity = false;
        }

        if (lightning_time > 0) {
            lightning = true;
        } else {
            lightning = false;
        }

        if (immunity) {
            if ((immunity_time -= dt) < 0) {
                immunity_time = 0;
            } else {
                immunity_time -= dt;
            }
        }

        if (!immunity) {
            imo_list_n = imo_list_next(obstacle_b_list, dt);
            for (int i = 0; i < imo_list_n.size(); i++) {
                ge211::Rect<float>
                        car_rect(car.top_left.x,
                                 car.top_left.y,
                                 car.body
                                    .width,
                                 car.body.height);
                if (imo_list_n[i].hits_block(car_rect)) {
                    life -= 1;
                    immunity_time += conf.immunity_while_being_hit;
                    obstacle_b_list[i] =
                            obstacle_b_list[obstacle_b_list.size() -
                                            1];
                    obstacle_b_list.pop_back();
                    break;
                }
            }
        }

        for(ge211::Rect<int> i: obstacle_a_list)
        {
            if(rect_collision(i,bo))
            {
                life-=1;
                immunity_time += conf.immunity_while_being_hit;
            }
        }

        imo_list_on_frame(heart_list, wall_list, dt);
        imo_list_on_frame(immunity_list, wall_list, dt);
        imo_list_on_frame(lightning_list, wall_list, dt);
        imo_list_on_frame_ob(obstacle_b_list,
                             wall_list,
                             dt,
                             conf.ob_boost_range);
    }
}




