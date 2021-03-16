//
// Created by Yunfan Yang on 3/4/21.
//

#include "fruit.hxx"


/// Contructor for fruit
fruit::fruit(fruit::Position center, bool live, int tier)
        :center_(center),
         velocity_(Game_config().fruit_velocity.height),
         live_(live),
         tier_(tier),
         config(Game_config())

{
    if (tier > config.fruit_tier || tier < 0){
        throw ge211::Client_logic_error
        ("We have not created that fruit yet!");
    }
};

int
fruit::get_radius()
{
    return fruit::tier_ * config.radius_increment + config.initial_radius;
};

fruit::Position
fruit::top_left(){
    int coordinate_x = center_.x - get_radius();
    int coordinate_y = center_.y - get_radius();
    return {coordinate_x, coordinate_y};
}

bool
fruit::overlapped(fruit other_fruit){
    int distance = (other_fruit.center_.x - center_.x) *
                    (other_fruit.center_.x - center_.x)
                     + (other_fruit.center_.y - center_.y) *
                     (other_fruit.center_.y - center_.y);
    int radius_sum = other_fruit.get_radius() + get_radius();
    return distance < radius_sum * radius_sum;
}

void
fruit::fruit_to(int x)
{
    if(!live_){
        center_.x = x;
    }
}

fruit
fruit::next(double dt){
    fruit result(*this);
    result.center_.y += result.velocity_ * dt;
    /// gradually increase the velocity of the ball to simulate gravity
    result.velocity_ += config.velocity_increment;
    return result;
}


bool
fruit::touch_bottom(){
    return center_.y > config.scene_dims.height - get_radius();
}

bool
fruit::touch_left_side(){
    return center_.x < get_radius();
}

bool
fruit::touch_right_side(){
    return center_.x >= config.scene_dims.width - get_radius();
}

bool
fruit::touch_edge(){
    return (touch_bottom() || touch_left_side() || touch_right_side());
}


fruit::Position
fruit::get_center()
{
    return center_;
}

bool
fruit::get_live()
{
    return live_;
}

int
fruit::get_tier()
{
    return tier_;
}

void
fruit::set_life(bool life)
{
    live_ = life;
}

void
fruit::move_center(int dx, int dy)
{
    center_.x += dx;
    center_.y += dy;
}

void
fruit::set_velocity(int vel)
{
    velocity_ = vel;
}

bool
operator==(fruit const &a, fruit const &b)
{
    return (a.tier_ == b.tier_) && (a.center_ == b.center_)
    && (a.live_ == b.live_);
}

std::ostream&
operator<<(std::ostream& o, fruit const &a)
{
    //This is for tests
    o << "fruit{";
    o << a.center_ << a.velocity_;
    if (a.live_){
        o << " true ";
    }else{
        o << " false ";
    }
    o << a.tier_;
    return o << "}";
}










