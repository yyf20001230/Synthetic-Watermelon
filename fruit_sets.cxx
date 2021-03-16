//
// Created by Yunfan Yang on 3/4/21.
//

#include "fruit_sets.hxx"

fruit_sets::fruit_sets()
    :score_(0),
     config(Game_config())
{
}

void
fruit_sets::group_overlapped()
{
    for (int i = 0; i < fruits.size(); i++){
        for (int j = i + 1; j < fruits.size(); j++) {
            if (fruits.at(i).overlapped(fruits.at(j))){

                /// if any two member of the set overlaps, make them still
                /// and reset their velocity
                fruits.at(i).set_life(false);
                fruits.at(j).set_life(false);
                fruits.at(i).set_velocity(config.fruit_velocity.height);
                fruits.at(j).set_velocity(config.fruit_velocity.height);

                /// reposition the overlapped pair by 1) checking which one is
                /// on top 2). reposition the higher fruit up until they are
                /// no longer touching, and then move down by 1 (tangent)
                if (fruits.at(j).get_center().y < fruits.at(i).get_center().y){
                    while (fruits.at(i).overlapped(fruits.at(j))){
                        fruits.at(j).move_center(0,-1);
                    }
                    fruits.at(j).move_center(0,1);
                }
                else{
                    while (fruits.at(j).overlapped(fruits.at(i))){
                        fruits.at(i).move_center(0,-1);
                    }
                    fruits.at(i).move_center(0,1);
                }
            }
        }
    }

}


void
fruit_sets::merge(){
    for (int i = 0; i < fruits.size(); i++){
        for (int j = i + 1; j < fruits.size(); j++){
            fruit first = fruits.at(i);
            fruit second = fruits.at(j);

            /// if the pair of two fruits with the same tier overlaps
            if (first.get_tier() == second.get_tier() && first.overlapped(second)){

                /// create a new fruit with the center located at the mid
                /// point of the two old fruits, with a state to true (make it
                /// fall, and with a tier one more than those two fruits
                /// being merged
                int coordinate_x = (first.get_center().x + second.get_center
                        ().x)/2;
                int coordinate_y = (first.get_center().y + second.get_center
                        ().y)/2;
                fruit new_fruit = fruit({coordinate_x,coordinate_y},true,
                                        first.get_tier() + 1);

                /// repositions the new fruit, delete two old fruits, and add
                /// the new one into the fruit set
                reposition(new_fruit);
                fruits.push_back(new_fruit);
                fruits.at(i) = fruits.back();
                fruits.pop_back();
                fruits.at(j) = fruits.back();
                fruits.pop_back();
                /// add point for each successful merge
                score_ += new_fruit.get_tier() -1 ;
            }
        }
    }

}



int
fruit_sets::all_overlapped(fruit& merged){
    int initial_height = 0;
    for (fruit& subject : fruits){
        /// We don't need to check overlapping with itself!
        if (&subject == &merged){
            continue;
        }
        /// get the max height of the overlapped fruit
        if (merged.overlapped(subject)){
            if (subject.get_center().y > initial_height){
                initial_height = subject.get_center().y;
            }
        }
    }
    return initial_height;
}


//precondition: merged is in the fruits list
void
fruit_sets::reposition(fruit& merged){
    /// if the new merged fruit touches the edge, move accordingly until it
    /// is no longer touching
    while (merged.touch_right_side()){
        merged.move_center(-1,0);
    }
    while (merged.touch_left_side()){
        merged.move_center(1,0);
    }

    while (merged.touch_bottom()){
        merged.move_center(0,-1);
    }

}

void
fruit_sets::float_check(){
    for (fruit& subject : fruits){

        /// There are two conditions that the fruit should fall.
        /// condition 1: the fruit is overlapping with some member, but they
        /// are all above the fruit
        if (all_overlapped(subject) != 0 && all_overlapped(subject) <
                                            subject.get_center().y){
            subject.set_life(true);

            /// reposition the fruit till it is tangent to the edges
            if (!subject.touch_edge()){
                subject.move_center(0,1);
            }
        }

        /// condition 2: the fruit isn't overlapping with any member, plus
        /// it's not touching the edges
        if (all_overlapped(subject) == 0 && !subject.touch_edge()) {
            subject.set_life(true);
        }

    }
}

int
fruit_sets::find_height(){
    int max_height = config.scene_dims.height;

    std::vector<fruit> set = fruits;

    /// make sure that the set isn't empty
    if (!set.empty()){
        set.pop_back();
    }

    /// get the max height of a dead fruit from the fruit set
    for (fruit subject : set){
        if (!subject.get_live()){
            if (subject.top_left().y < max_height){
                max_height = subject.top_left().y;
            }
        }
    }
    return max_height;
}


int
fruit_sets::live_fruit()
{
  int temp = config.scene_dims.height;

  /// get the max height of a live fruit from the fruit set
  for (fruit subject : fruits){
      if (subject.get_center().y - subject.get_radius() < temp && subject
      .get_live()){
          temp = subject.get_center().y;
      }
  }
  return temp;
}


int
fruit_sets::find_max_tier()
{
    int tier = 1;

    /// get the max tier of a fruit from the fruit set
    for (fruit subject : fruits){
        if (subject.get_tier() > tier){
            tier = subject.get_tier();
        }
    }
    return tier;
}

void
fruit_sets::set_score(int new_score)
{
    score_ = new_score;
}

int
fruit_sets::get_score()
{
    return score_;
}

std::vector<fruit>*
fruit_sets::get_fruits()
{
    return &fruits;
}

void
fruit_sets::add_fruits(fruit new_fruit)
{
    fruits.push_back(new_fruit);
}

void
fruit_sets::clear_fruits()
{
    fruits.clear();
}




