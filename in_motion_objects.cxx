//
// Created by 曹先生 on 2021/5/30.
//

#include "in_motion_objects.hxx"
#include "cmath"

in_motion_object::in_motion_object(ge211::Dims<float> v,
                                   ge211::Posn<float> c,
                                   int r)
        :velocity(v),center(c),radius(r)
{
}

void
in_motion_object::print_imo()
{
    printf("printing in_motion_object... \n");
    printf("center: x = %f   ", center.x);
    printf("y = %f \n", center.y);
    printf("radius = %d  \n", radius);
    printf("velocity: width = %f    ",velocity.width);
    printf("height = %f\n",velocity.height);
}

void print_imo_list(std::vector<in_motion_object> list)
{
    for(in_motion_object i: list)
    {
        i.print_imo();
    }
}

in_motion_object imo_generator(int hv_low,int hv_up,int vv_low, int vv_up,
                               int x_low, int x_up, int y_low, int y_up,
                               int r)
{
    ge211::Random_source<float> y_generator(y_low,y_up);

    ge211::Random_source<float>
            hv_generator(hv_low,hv_up);

    ge211::Random_source<float>
            vv_generator(vv_low,
                         vv_up);

    ge211::Random_source<float>
            x_generator(x_low, x_up);

    float hv = hv_generator.next();
    float vv = vv_generator.next();

    while(hv == 0 || vv == 0)
    {
        if(hv == 0)
        {
            hv=hv_generator.next();
        }
        if(vv == 0)
        {
            vv=vv_generator.next();
        }
    }

    in_motion_object a({hv, vv},
                       {x_generator.next(),y_generator.next()},r);
    return a;
}


in_motion_object
in_motion_object::next(double dt) const
{
    in_motion_object result(*this);
    result.center.x = center.x + dt*velocity.width;
    result.center.y = center.y + dt*velocity.height;
    return result;
}

std::vector<int>
in_motion_object::collided_side(ge211::Rect<int> block)
{
    std::vector<int> return_list(2);
    if((center.x + radius)<block.x ||(center.x - radius)>block.x+block.width)
    {
        return_list[0] = 0;
    }
    else
    {
        if(center.x <= block.x+block.width/2)
        {
            return_list[0] = -1;
        }
        else
        {
            return_list[0] = 1;
        }
    }
    if((center.y + radius)<block.y ||(center.y - radius)>block.y+block.height)
    {
        return_list[1] = 0;
    }
    else
    {
        if(center.y <= block.y+block.height/2)
        {
            return_list[1] = -1;
        }
        else
        {
            return_list[1] = 1;
        }
    }
    return return_list;
}

bool
in_motion_object::hits_block(ge211::Rect<int> block)
{
    if((center.x + radius) < block.x || (center.x - radius)>(block
                                                                     .x+block.width))
    {
        return false;
    }
    if((center.y + radius) < block.y || (center.y - radius)>(block.y+
                                                             block.height))
    {
        return false;
    }
    return true;
}

bool
in_motion_object::hits_block(ge211::Rect<float> block)
{
    if((center.x + radius) < block.x || (center.x - radius)>(block
    .x+block.width))
    {
        return false;
    }
    if((center.y + radius) < block.y || (center.y - radius)>(block.y+
                                                             block.height))
    {
        return false;
    }
    return true;
}

void
in_motion_object::reflect_vertical()
{
    velocity.height *= -1;
}

void
in_motion_object::reflect_horizontal()
{
    velocity.width *= -1;
}

ge211::Posn<float>
in_motion_object::top_left() const
{
    float x = center.x - radius;
    float y = center.y - radius;
    return {x,y};
}

