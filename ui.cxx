#include "ui.hxx"



UI::UI(Model& model)
        : model(model),
          builder(score_font)
{ }

ge211::Dims<int>
UI::initial_window_dimensions() const
{
    return {model.config.scene_dims.width,model.config.scene_dims.height};
}

void
UI::draw(ge211::Sprite_set& set){

    /// set game over if the player wins (max tier reached) or loses (fruit
    /// stack too high
    if (model.get_set().find_height() < model.config.top_margin ||
        model.get_set().find_max_tier() == model.config.fruit_tier) {
        model.set_game(true);
    }

    /// add sprite for the generated fruit as well as the fruit set, with
    /// sprite for game in process
    if (!model.check_is_game_over() || model.get_set().find_max_tier() ==
    model.config.fruit_tier){
        for (auto fruit : *model.get_set_ptr()->get_fruits()){
            switch (fruit.get_tier()){
            case 1: set.add_sprite(tier_1_sprite,fruit.top_left());
                break;
            case 2: set.add_sprite(tier_2_sprite,fruit.top_left());
                break;
            case 3: set.add_sprite(tier_3_sprite,fruit.top_left());
                break;
            case 4: set.add_sprite(tier_4_sprite,fruit.top_left());
                break;
            case 5: set.add_sprite(tier_5_sprite,fruit.top_left());
                break;
            case 6: set.add_sprite(tier_6_sprite,fruit.top_left());
                break;
            case 7: set.add_sprite(tier_7_sprite,fruit.top_left());
                break;
            }


        }
        switch (model.get_generated_fruit().get_tier()){
        case 1: set.add_sprite(tier_1_sprite,model.
        get_generated_fruit().top_left());
            break;
        case 2: set.add_sprite(tier_2_sprite,
                               model.get_generated_fruit().top_left());
            break;
        case 3: set.add_sprite(tier_3_sprite,
                               model.get_generated_fruit().top_left());
            break;
        case 4: set.add_sprite(tier_4_sprite,
                               model.get_generated_fruit().top_left());
            break;
        case 5: set.add_sprite(tier_5_sprite,
                               model.get_generated_fruit().top_left());
            break;
        case 6: set.add_sprite(tier_6_sprite,
                               model.get_generated_fruit().top_left());
            break;
        case 7: set.add_sprite(tier_7_sprite,
                               model.get_generated_fruit().top_left());
            break;
        }

        /// add a score to the screen in the corner if the game is not winning
        if (!model.check_is_game_over()){
            builder << std::to_string(model.get_set().get_score());
            score_text.reconfigure(builder);
            builder.message("");
            set.add_sprite(score_text,{model.config.
                                              restart_button.width - 10,
                                              0},3);
        }


        /// if the stack of fruit is approaching the warning line
        if (model.get_set().find_height() < model.config.warning_line){
            set.add_sprite(white_line_sprite,{0,
            model.config.top_margin},1);
        }

        /// if the player is winning the game
        if (model.get_set().find_max_tier() == model.config.fruit_tier){
            model.set_game(true);
            set.add_sprite(winning_text,{model.config.scene_dims.width / 2 -
                                         model.config.game_over_coordinate,model
                                         .config.scene_dims.height / 2 -
                                         model.config
                                         .score_text_shifting_const},
                                         2);
            builder << "Score:" << std::to_string
                                    (model.get_set().get_score());
            score_text.reconfigure(builder);
            builder.message("");
            set.add_sprite(score_text,{model.config.scene_dims.width/2 -
                              model.config.shifting_const,model.config
                              .scene_dims.height / 2 },2);
            set.add_sprite(restart_sprite,{model.config.restart_button.width,
                                           model.config.restart_button
                                                .height},2);
        }

        /// add a pause button to the game
        set.add_sprite(pause_sprite,{model.config.pause_button.width,
                                     model.config.pause_button.height},2);

    }

    /// if the game is lost, add game over sprite to fruit set only. No
    /// more fruit will be generated. Show a restart button and a game over text
    else{
        for (fruit subject : *model.get_set_ptr()->get_fruits()){
            switch (subject.get_tier()){
            case 1: set.add_sprite(game_over_sprite_1,subject.top_left());
                break;
            case 2: set.add_sprite(game_over_sprite_2,subject.top_left());
                break;
            case 3: set.add_sprite(game_over_sprite_3,subject.top_left());
                break;
            case 4: set.add_sprite(game_over_sprite_4,subject.top_left());
                break;
            case 5: set.add_sprite(game_over_sprite_5,subject.top_left());
                break;
            case 6: set.add_sprite(game_over_sprite_6,subject.top_left());
                break;
            case 7: set.add_sprite(game_over_sprite_7,subject.top_left());
                break;
            }
        }

        /// add a restart button, a game over text, as well as a score
        set.add_sprite(restart_sprite,{model.config.restart_button.width,
                                           model.config.restart_button
                                          .height},2);
        set.add_sprite(game_over_text,{model.config.scene_dims.width / 2 -
                          185,model.config.scene_dims.height / 2
                          - model.config.score_text_shifting_const},1);

        builder << "Score:" << std::to_string(model.get_set().get_score());
        score_text.reconfigure(builder);
        builder.message("");
        set.add_sprite(score_text,{model.config.scene_dims.width/2 - model
        .config.shifting_const,
                                 model.config.scene_dims.height / 2 },2);

    }
    set.add_sprite(background_sprite,{0,0},-1);

    /// if the game is paused (not winning and losing), show a paused text, and
    /// temporarily clear the screen
    if (model.check_is_paused() && !model.check_is_game_over() &&
    model.get_set().find_max_tier() < model.config.fruit_tier){
        set.add_sprite(background_sprite,{0,0},1);
        set.add_sprite(pause_text,{model.config.scene_dims.width / 2 - 105,
                                    model.config.scene_dims.height /2 -
                                    model.config.score_text_shifting_const},2);
    }
}

void
UI::on_mouse_up(ge211::Mouse_button button, ge211::Posn<int> position){

    /// if the stack is too high, set game over
    if (model.get_set().find_height() < model.config.top_margin) {
        model.set_game(true);
    }

    /// if the game is not over
    if (!model.check_is_game_over()){

        /// if the pause button is clicked, pause the game
        if (position.x > model.config.pause_button.width && position.x <
                         model.config.pause_button.width +
                         model.config
                         .restart_button_radius &&
            position.y > model.config.pause_button.height &&
            position.y < model.config.pause_button.height +
            model.config.restart_button_radius){
            model.pause_game();
        }

        /// if the game is not paused, the winning condition isn't reached, and
        /// the button is not being clicked, generate a random new fruit
        else{
            if (!model.check_is_paused() && model.get_set().find_max_tier() <
            model.config.fruit_tier){

                /// Determine the fruit that can be spawned at the top
                /// depending on the max tier gained by the player
                int tier;
                if (model.get_set().find_max_tier() <= 2){
                    tier = ge211::Random_source<int>(1,2).next();
                }
                else{
                    tier = ge211::Random_source<int>(1,model.get_set()
                    .find_max_tier() - 2).next();
                }

                fruit new_fruit = fruit({position.x,model.config.top_margin
                                         },false,tier);

                /// If the previous fruit has fallen far enough, make the new
                /// fruit fall, and add it to the fruit set.
                if (model.get_set().live_fruit() > model.config.top_margin +
                new_fruit.get_radius() + 5){
                    model.get_generated_fruit_ptr()->set_life(true);
                    model.get_set_ptr()->add_fruits(model.
                                                    get_generated_fruit());
                    model.set_generated_fruit(new_fruit);

                    /// reposition the fruit so that it doesn't touch both
                    /// sides of the screen
                    while (model.get_generated_fruit().touch_left_side()){
                        model.get_generated_fruit_ptr()->move_center(1,0);
                    }
                    while (model.get_generated_fruit().touch_right_side()){
                        model.get_generated_fruit_ptr()->move_center(-1,0);
                    }
                }
            }
        }
    }
    else{
        /// if the game is over (winning or losing), show a restart button for
        /// the player to restart the game
        if (position.x > model.config.restart_button.width && position.x <
                model.config.restart_button.width +
                model.config.restart_button_radius &&
                position.y > model.config.restart_button.height &&
                position.y < model.config.restart_button.height + model
                .config.restart_button_radius){
            model.reset_game();
        }
    }


}

void
UI::on_mouse_move(ge211::Posn<int> position){

    /// move the fruit according to the mouse position if the game is not
    /// paused. Stop the fruit if the mouse is going outside of the screen
    /// border.
    if (!model.check_is_paused()){
        if (position.x > model.get_generated_fruit().get_radius() &&
            position.x < model.config.scene_dims.width - model
            .get_generated_fruit().get_radius()){
            model.get_generated_fruit_ptr()->fruit_to(position.x);
        }
    }
}

void
UI::on_frame(double dt){
    model.on_frame(dt);
}

