#pragma once

#include "model.hxx"
#include <ge211.hxx>


struct UI
        : ge211::Abstract_game
{
    //
    // CONSTRUCTOR
    //
public:
    explicit UI(Model&);

    //
    // MEMBER FUNCTIONS (for the view)
    //

protected:
    ge211::Dims<int> initial_window_dimensions() const override;
    void draw(ge211::Sprite_set&) override;
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;
    void on_mouse_move(ge211::Posn<int>) override;
    void on_frame(double dt) override;

//private:
    //
    // MEMBER VARIABLE (model reference)
    //

    Model& model;

private:
    /// Color for the background of the game
    ge211::Rectangle_sprite const
            background_sprite{initial_window_dimensions(),
                              ge211::Color(237,229,128)};

    /// Color for the fruit when it's game over

    int color = model.config.color_const;

    ge211::Circle_sprite const
            game_over_sprite_1{model.config.initial_radius + model.config
            .radius_increment,ge211::Color(0,color,color)};
    ge211::Circle_sprite const
            game_over_sprite_2{model.config.initial_radius + 2 * model.config
            .radius_increment,ge211::Color(color,color,color)};
    ge211::Circle_sprite const
            game_over_sprite_3{model.config.initial_radius + 3 * model.config
            .radius_increment,ge211::Color(2 * color,color,color)};
    ge211::Circle_sprite const
            game_over_sprite_4{model.config.initial_radius + 4 * model.config
            .radius_increment,ge211::Color(3 * color,color,color)};
    ge211::Circle_sprite const
            game_over_sprite_5{model.config.initial_radius + 5 * model.config
            .radius_increment,ge211::Color(4 * color,color,color)};
    ge211::Circle_sprite const
            game_over_sprite_6{model.config.initial_radius + 6 * model.config
            .radius_increment,ge211::Color(5 * color,color,color)};
    ge211::Circle_sprite const
            game_over_sprite_7{model.config.initial_radius + 7 * model.config
            .radius_increment,ge211::Color(6 * color,color,color)};

    /// Color for the fruit when the game is in process
    ge211::Image_sprite const
            tier_1_sprite{"tier1.png"};
    ge211::Image_sprite const
            tier_2_sprite{"tier2.png"};
    ge211::Image_sprite const
            tier_3_sprite{"tier3.png"};
    ge211::Image_sprite const
            tier_4_sprite{"tier4.png"};
    ge211::Image_sprite const
            tier_5_sprite{"tier5.png"};
    ge211::Image_sprite const
            tier_6_sprite{"tier6.png"};
    ge211::Image_sprite const
            tier_7_sprite{"tier7.png"};
    ge211::Rectangle_sprite const
            white_line_sprite{{model.config.scene_dims.width,5},
                              ge211::Color(model.config.gray_color,model
                              .config.gray_color,model.config.gray_color)};

    /// sprite and texts for game over
    ge211::Text_sprite game_over_text
            {"GAME OVER!",{"sans.ttf",model.config.text_size}};
    ge211::Image_sprite const
            restart_sprite{"restart.png"};


    /// sprite and texts for game pause
    ge211::Text_sprite pause_text
            {"Paused",{"sans.ttf",model.config.text_size}};
    ge211::Image_sprite const
            pause_sprite{"pause.png"};

    /// sprite for a winning game
    ge211:: Text_sprite winning_text
            {"You win!",{"sans.ttf",model.config.text_size}};

    /// sprite for a score text
    ge211::Text_sprite score_text
            {"",{"sans.ttf",model.config.text_size}};

    ge211:: Font score_font = {"sans.ttf",model.config.text_size};
    ge211:: Text_sprite:: Builder builder;

};