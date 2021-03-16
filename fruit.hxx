//
// Created by Yunfan Yang on 3/4/21.
//
#pragma once

#include <ge211.hxx>
#include "game_config.hxx"

///represents every individual member of fruit
class fruit{


public:

    /// the position of each fruit will use int coordinates
    using Position = ge211::Posn<int>;

    /// each fruit is constructed with a center, a state (whether the fruit
    /// should move or not), and a tier
    explicit fruit(fruit::Position,bool,int);

    /// returns the radius of the fruit based on its radius
    /// error: Throws `ge211::Client_logic_error`
    ///       if the tier is below 1 or greater than 7
    int get_radius();

    /// returns the top left coordinate of the fruit
    Position top_left();

    /// check if the fruit overlaps with another. Returns true if they are
    /// overlapped
    bool overlapped(fruit);

    /// move the fruit horizontally, used in on_mouse_move
    void fruit_to(int);

    /// check if the fruit touches the right side of the screen. Returns true
    /// if it touches
    bool touch_right_side();

    /// check if the fruit touches the left side of the screen. Returns true
    /// if it touches
    bool touch_left_side();

    ///check if the fruit touches the bottom of the screen. Returns true if
    ///it touches
    bool touch_bottom();

    /// check if the fruit touches the edge (left, right, bottom) of the
    /// screen. Returns true if it touches
    bool touch_edge();

    /// Returns the state of the fruit after `dt` seconds have passed,
    /// were it to move freely (without obstacles).
    fruit next(double);

    /// get the center of the fruit
    Position get_center();

    /// get the state of the fruit
    bool get_live();

    /// get the tier of the fruit
    int get_tier();

    /// set the state of the fruit equal to the input
    void set_life(bool);

    /// move the center of the fruit by an amount specified in the input
    /// for example, move_center(0,1) would move the fruit down by 1 (y++)
    void move_center(int,int);

    /// set the velocity of the fruit equal to the input
    void set_velocity(int);

private:
    //member variables

    /// We will represent positions as GE211 `Posn<int>`s, which we alias
    /// with the type name `Position`. This reprents the coordinate of the
    /// center of the fruit
    Position center_;

    /// We will represent velocities as GE211 `Dims<int>`s, which we alias
    /// with the type name `Velocity`.
    int velocity_;

    /// Whether the fruit is moving freely (true) or it already landed (false)
    bool live_;

    /// A tier of the fruit. The greater the tier, the greater the radius.
    /// The ultimate goal is to make a fruit with tier 7
    int tier_;


    /// The configuration parameters of the fruit. See game_config.hxx for a
    /// description of what this determines. Models can be constructed with
    /// different configurations, but the configuration never changes on an
    /// existing fruit.
    Game_config config;

    /// Compares two fruits for equality. Two fruits are equal if all their
    /// member variables are pairwise equal.
    friend bool operator==(fruit const&, fruit const&);

    /// Stream insertion (printing) for fruit.
    friend std::ostream& operator<<(std::ostream&, fruit const&);

};






