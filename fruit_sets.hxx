//
// Created by Yunfan Yang on 3/4/21.
//

#pragma once

#include "fruit.hxx"
#include <ge211.hxx>
#include "game_config.hxx"

class fruit_sets{


public:

    // member functions

    /// the default constructor of fruit sets. Fruit sets contain all the
    /// fruit that are stacked in the UI as well as the falling fruits
    explicit fruit_sets();

    /// loop through each member of the fruit sets. If a pair of fruit
    /// overlaps each other, set both of their state to false, and reset their
    /// velocity. Then, reposition the overlapped fruits to make sure that they
    /// are tangent and no longer overlapped.
    void group_overlapped();

    /// look through each member of the fruit set. If a pair of fruit
    /// overlaps each other and have the same tier, delete both of them, and
    /// add a fruit with larger tier into the fruit set. Helper function
    /// reposition will be used to make sure the merged fruit is created
    /// correctly. The player would get 1 point from a successful merge.
    void merge();

    /// Helper function of merge. Reposition function make sure that the
    /// merged fruit is placed in the right position. This is used to account
    /// for situations that the merged fruit is created inside the edge or
    /// inside other fruits
    void reposition(fruit&);

    /// Check if any member of the fruit sets is overlapped with the fruit
    /// from the input. This is mainly used to detect whether the new merged
    /// fruit is located in its correct position. The function returns the
    /// y value of the highest fruit overlapping the merged fruit (which will
    /// later be used in float check), and it returns 0 if otherwise.
    int all_overlapped(fruit&);

    /// returns the highest y value of a live fruit in the fruit set. This is
    /// used to make sure that no fruits will be dropped at the same time,
    /// cauing an unexpected game-over from two overlapped member floating on
    /// top of the screen.
    int live_fruit();

    /// check if any member of the fruit set is floating. If so, set their
    /// state to true so that they can fall down. This function is
    /// responsible for making sure none of the fruit will be floating after a
    /// successful merge.
    void float_check();

    /// returns the highest y value of a dead fruit in the fruit set. This is
    /// used to determine when the game is over.
    int find_height();

    /// returns the highest tier of a fruit in the fruit set. This is used to
    /// determine when the player clears the game.
    int find_max_tier();

    void set_score(int);
    int get_score();

    std::vector<fruit>* get_fruits();
    void add_fruits(fruit);
    void clear_fruits();



private:
    //member variables

    /// the score of the game. Player gets a point equal to two raised
    /// to the power of the tier of the merged fruit whenever there is a
    /// successful fruit merge
    int score_;

    /// the fruit set that appears on the screen
    std::vector<fruit> fruits;

    /// The configuration parameters of the fruit. See game_config.hxx for a
    /// description of what this determines. Models can be constructed with
    /// different configurations, but the configuration never changes on an
    /// existing fruit.
    Game_config config;
};

