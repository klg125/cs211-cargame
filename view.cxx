#include "view.hxx"

//blue
static ge211::Color const obstacle_b_color{7, 27, 245};
//pink
static ge211::Color const heart_color{245, 7, 90};
//bright yellow
static ge211::Color const lightning_color{239, 245, 66};
//purple
static ge211::Color const immunity_color{166, 7, 245};
//red
static ge211::Color const obstacle_a_color{245, 27, 7};
//grey
static ge211::Color const wall_color_c{128,128,128};
//grey
static ge211::Color const trophy_color{50,50,50};
//grey
static ge211::Color const car_color{255,255,255};


View::View(Model& model)
    : model_(model),
    heart_sprite(model.conf.bi_radius,heart_color),
    immunity_sprite(model.conf.bi_radius,immunity_color),
    lightning_sprite(model.conf.bi_radius,lightning_color),
    obstacle_b_sprite(model.conf.obstacle_b_radius,obstacle_b_color),
    obstacle_a_sprite(model.conf.obstacle_a_body,obstacle_a_color),
    trophy_sprite(model.conf.trophy_dims,trophy_color),
    car_sprite_image(ge211::Image_sprite("car2.jpg")),
    trophy_image(ge211::Image_sprite("trophy_2.png")),
    lives(ge211::Image_sprite("gold_lives.png")),
    lightning_image(ge211::Image_sprite("lightning.png")),
    immunity_image(ge211::Image_sprite("immunity.png")),
    car_sprite(model.car.body,car_color),
    help_font_("sans.ttf", 30),
    lost_message(ge211::Text_sprite::Builder(help_font_)
                             .add_message("You have lost :( Press r to play "
                                          "again.")
                             .color(ge211::Color::white())
                             .build()),
    win_message(ge211::Text_sprite::Builder(help_font_)
                       .add_message("You have won! :) Press r to play again")
                       .color(ge211::Color::white())
                       .build())
{
    for(ge211::Rect<int> i:model_.wall_list)
    {
        ge211::Rectangle_sprite wall_sprite(i.dimensions(),wall_color_c);
        wall_list.push_back(wall_sprite);
        wall_top_left_list.push_back(i.top_left());
    }
}

void
print_posn(ge211::Posn<int> pos)
{
    printf("printing posn... \n");
    printf("x = %d y = %d \n",pos.x,pos.y);
}

//function to add a circle sprite
void
add_circle_sprite(ge211::Sprite_set& set,ge211::Circle_sprite& spr,
                  ge211::Posn<int> pos)
{
    set.add_sprite(spr,pos);
}

//function to add all circle sprites for in motion objects
void
add_circle_sprite_in_list(ge211::Sprite_set& set, ge211::Circle_sprite& spr,
                          std::vector<in_motion_object> list)
{
    for(in_motion_object i: list)
    {
        ge211::Posn<int> pos= {static_cast<int>(i.top_left().x),
                               static_cast<int>(i.top_left().y)};
        add_circle_sprite(set,spr,pos);
    }
}

//function to add a image sprite
void
add_image_sprite(ge211::Sprite_set& set,ge211::Image_sprite& spr,
                  ge211::Posn<int> pos)
{
    set.add_sprite(spr,pos, 5);
}

//function to add all image sprites for in motion objects
void
add_image_sprite_in_list(ge211::Sprite_set& set, ge211::Image_sprite& spr,
                          std::vector<in_motion_object> list)
{
    for(in_motion_object i: list)
    {
        ge211::Posn<int> pos= {static_cast<int>(i.top_left().x-1),
                               static_cast<int>(i.top_left().y-1)};
        add_image_sprite(set,spr,pos);
    }
}

// implements draw function
void
View::draw(ge211::Sprite_set& sprites)
{
    if (model_.game_end)
    {
        ge211::Dims<int> a ={model_.conf.scene_width,
                             model_.conf.scene_height+model_.conf
                             .bottom_display_height};
        if(model_.game_win)
        {
            sprites.add_sprite(win_message,{400,400});
        }
        else
        {
            sprites.add_sprite(lost_message,{400,400});
        }
    }
    else {
        add_circle_sprite_in_list(sprites, heart_sprite, model_.heart_list);
        add_image_sprite_in_list(sprites, lives, model_.heart_list);

        add_circle_sprite_in_list(sprites, heart_sprite, model_.heart_list);

        add_circle_sprite_in_list(sprites,
                                  lightning_sprite,
                                  model_.lightning_list);

        add_image_sprite_in_list(sprites,
                                  lightning_image,
                                  model_.lightning_list);

        add_circle_sprite_in_list(sprites,
                                  immunity_sprite,
                                  model_.immunity_list);

        add_image_sprite_in_list(sprites,
                                  immunity_image,
                                  model_.immunity_list);

        add_circle_sprite_in_list(sprites, obstacle_b_sprite,
                                  model_.obstacle_b_list);

        for (ge211::Rect<int> i:model_.obstacle_a_list) {
            sprites.add_sprite(obstacle_a_sprite, i.top_left());
        }

        for (int i = 0; i < wall_top_left_list.size(); i++) {
            sprites.add_sprite(wall_list[i], wall_top_left_list[i]);
        }

        sprites.add_sprite(trophy_sprite,model_.conf.trophy_top_left);

        sprites.add_sprite(trophy_image,model_.conf.trophy_top_left, 5);

        sprites.add_sprite(car_sprite,
                           posn_float_to_int(model_.car.top_left));

        sprites.add_sprite(car_sprite_image,
                           posn_float_to_int(model_.car.top_left), 5);

    }
}