//
// Created by 曹先生 on 2021/5/29.
//
#include "cmath"
#include "car.hxx"
#include "in_motion_objects.hxx"

#define PI 3.14159265

Car::Car(Game_config config)
        :speed(0),
        angle(0),
        velocity({speed,0}),
        top_left(config.car_start_position),
        body({config.car_width,config.car_height}),
        max_speed(config.max_car_speed)
{

}

void print_posn(ge211::Posn<float> a)
{
    printf("Position: %f %f",a.x,a.y);
}

ge211::Posn<int> posn_float_to_int(Position a)
{
    int x = static_cast<int>(a.x);
    int y = static_cast<int>(a.y);
    return {x,y};
}

Car
Car::on_next_frame(double dt)
{
    Car new_car(*this);
    new_car.angle = new_car.angle%4;

    int real_angle;
    if(new_car.angle<0)
    {
        real_angle=new_car.angle+4;
    }
    else
    {
        real_angle=new_car.angle;
    }

    if(real_angle==0)
    {
        new_car.velocity={speed,0};
    }
    else if(real_angle==1)
    {
        new_car.velocity={0,speed};
    }
    else if(real_angle==2)
    {
        new_car.velocity={-speed,0};
    }
    else if(real_angle==3)
    {
        new_car.velocity={0,-speed};

    }

    new_car.top_left+=new_car.velocity;
    return new_car;
}
