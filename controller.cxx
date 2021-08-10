#include "controller.hxx"

Controller::Controller(Model& m)
        : model_(m),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

ge211::Dims<float> clockwise_rotation(ge211::Dims<float> v)
{
    return {v.height,-v.width};
};

ge211::Dims<float> anticlockwise_rotation(ge211::Dims<float> v)
{
    return {-v.height,v.width};
};

void add_speed(ge211::Dims<float> & v,int acceleration,int angle,float
max_speed)
{
    if(angle==0)
    {
        if(v.width+acceleration>=max_speed)
        {
            v.width=max_speed;
        }
        else
        {
            v += ge211::Dims<float> {static_cast<float>(acceleration), 0};
        }
    }
    else if(angle==1)
    {
        if(v.height+acceleration>=max_speed)
        {
            v.height=max_speed;
        }
        else
        {
            v += ge211::Dims<float> {0, static_cast<float>(acceleration)};
        }
    }
    else if(angle==2)
    {
        if(v.width-acceleration<=max_speed)
        {
            v.width=-max_speed;
        }
        else
        {
            v += ge211::Dims<float> {-static_cast<float>(acceleration), 0};
        }
    }
    else
    {
        if(v.height-acceleration<=max_speed)
        {
            v.height=-max_speed;
        }
        else
        {
            v += ge211::Dims<float> {-static_cast<float>(acceleration), 0};
        }
    }
}

void reduce_speed(ge211::Dims<float> & v,int acceleration,int angle,float
max_speed)
{
    if(angle==0)
    {
        if(v.width-acceleration<=0)
        {
            v.width=0;
        }
        else
        {
            v -= ge211::Dims<float> {static_cast<float>(acceleration), 0};
        }
    }
    else if(angle==1)
    {
        if(v.height-acceleration<=0)
        {
            v.height=max_speed;
        }
        else
        {
            v -= ge211::Dims<float> {0, static_cast<float>(acceleration)};
        }
    }
    else if(angle==2)
    {
        if(v.width+acceleration>=0)
        {
            v.width=0;
        }
        else
        {
            v -= ge211::Dims<float> {-static_cast<float>(acceleration), 0};
        }
    }
    else
    {
        if(v.height+acceleration>=max_speed)
        {
            v.height=0;
        }
        else
        {
            v -= ge211::Dims<float> {-static_cast<float>(acceleration), 0};
        }
    }
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
    else if(key == ge211::Key::code('r'))
    {
        Model m;
        model_=m;
    }
    else if(key == ge211::Key::code('w'))
    {
        if(model_.car.speed+model_.conf.default_acceleration>=model_.car
        .max_speed)
        {
            model_.car.speed = model_.car.max_speed;
        }
        else
        {
            model_.car.speed+=model_.conf.default_acceleration;
        }
    }
    else if(key == ge211::Key::code('s'))
    {
        if(model_.car.speed+model_.conf.default_acceleration<=0)
        {
            model_.car.speed = 0;
        }
        else
        {
            model_.car.speed-=model_.conf.default_acceleration;
        }
    }
    else if(key == ge211::Key::code('a'))
    {
        model_.car.angle-=1;
        /*
        model_.car.velocity=clockwise_rotation(model_.car.velocity);
        */
    }
    else if(key == ge211::Key::code('d'))
    {
        model_.car.angle+=1;
        /*
        model_.car.velocity=anticlockwise_rotation(model_.car.velocity);
        */
    }
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return {model_.conf.scene_width,
            model_.conf.scene_height+model_.conf.bottom_display_height};
}


void
Controller::on_frame(double dt)
{
    view_.model_.on_frame(dt);
}

