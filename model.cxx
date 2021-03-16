#include "model.hxx"
#include "fruit.hxx"
#include "fruit_sets.hxx"



Model::Model(Game_config const& config)
        :  config(Game_config()),
           set_(fruit_sets()),
           generated_fruit(fruit({Game_config().scene_dims.width / 2,
                                  Game_config().top_margin},false,1)),
           is_game_over(false),
           is_paused(false)

{
}

void
Model::on_frame(double dt){


    for (fruit& subject : *set_.get_fruits()){

        /// if the next frame of the fruit touches any edge, make it stop
        /// (false), then reposition it so that it is tangent to the edge
        if (subject.next(dt).touch_edge()){
            subject.set_life(false);
            while (subject.touch_edge()){
                subject.move_center(0,-1);
            }
            while (!subject.touch_edge()){
                subject.move_center(0,1);
            }
        }

        /// if else, update each live member in the fruit sets
        else{
            if (subject.get_live()){
                subject = subject.next(dt);
            }
        }
    }

    /// check for merge, overlap, and float
    set_.merge();
    set_.group_overlapped();
    set_.float_check();

}

void Model::reset_game(){
    set_.clear_fruits();
    is_game_over = false;
    generated_fruit = fruit({Game_config().scene_dims.width / 2,
                                   Game_config().top_margin},
                                  false,1);
    set_.set_score(0);
}

void Model::pause_game(){
    is_paused = !is_paused;
}

void
Model::set_game(bool game)
{
    is_game_over = game;
}

bool
Model::check_is_game_over()
{
    return is_game_over;
}

fruit
Model::get_generated_fruit()
{
    return generated_fruit;
}

fruit_sets *
Model::get_set_ptr()
{
    return &set_;
}

fruit_sets
Model::get_set()
{
    return set_;
}

bool
Model::check_is_paused()
{
    return is_paused;
}

fruit *
Model::get_generated_fruit_ptr()
{
    return &generated_fruit;
}

void
Model::set_generated_fruit(fruit new_fruit)
{
    generated_fruit = new_fruit;
}






