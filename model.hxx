#pragma once

#include <ge211.hxx>
#include "fruit.hxx"
#include "fruit_sets.hxx"
#include "game_config.hxx"
#include <vector>

struct Model{

public:
    explicit Model(Game_config const& config = Game_config());
    void reset_game();
    void pause_game();
    void on_frame(double);

    /// The configuration parameters of the model. See game_config.hxx for a
    /// description of what this determines. Models can be constructed with
    /// different configurations, but the configuration never changes on an
    /// existing model.
    Game_config const config;

    // Check
    void set_game(bool);
    bool check_is_game_over();
    fruit_sets get_set();
    fruit_sets* get_set_ptr();
    fruit get_generated_fruit();
    fruit* get_generated_fruit_ptr();
    bool check_is_paused();
    void set_generated_fruit(fruit);

private:

    /// the fruit set that are stacked on the screen
    fruit_sets set_;

    /// the randomly generated fruit appears at the top of the screen
    fruit generated_fruit;

    /// whether the game is over
    bool is_game_over;

    /// whether the game is paused
    bool is_paused;
};


