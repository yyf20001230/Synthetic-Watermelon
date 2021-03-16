

#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : pause_button_coordinate{20},
          game_over_coordinate{115},
          scene_dims{600,800},
          fruit_velocity{0,10},
          pause_button{pause_button_coordinate,pause_button_coordinate},
          restart_button{scene_dims.width - 100,25},
          top_margin(100),
          fruit_tier(7),
          radius_increment(15),
          initial_radius(10),
          warning_line(300),
          velocity_increment(14),
          gray_color(150),
          shifting_const(155),
          color_const(40),
          text_size(60),
          score_text_shifting_const(65),
          restart_button_radius(75)


{ }

