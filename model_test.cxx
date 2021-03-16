#include "model.hxx"

#include <catch.hxx>

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//



TEST_CASE("Passes with starter code")
{
    Model m;
    CHECK_FALSE(m.check_is_game_over());
    CHECK_FALSE(m.check_is_paused());
    CHECK(m.get_generated_fruit() == fruit({300,100},false,1));
    CHECK(m.get_set().get_fruits()->empty());

    m.pause_game();
    CHECK(m.check_is_paused());
    m.pause_game();
    m.set_game(true);
    CHECK(m.check_is_game_over());
    m.reset_game();
    CHECK(m.get_set().get_fruits()->empty());
    CHECK(m.get_set().get_score() == 0);
}


TEST_CASE("Group Overlapped")
{
    Model m;
    fruit_sets set = m.get_set();

    set.add_fruits(fruit({100,400},true,1));
    set.add_fruits(fruit({100,336},true,2));
    set.group_overlapped();
    CHECK(set.get_fruits()->at(0) == fruit({100,400},false,1));
    CHECK(set.get_fruits()->at(1) == fruit({100,336},false,2));

    set.add_fruits(fruit({300,400},true,1));
    set.add_fruits(fruit({300,390},true,2));
    set.group_overlapped();
    CHECK(set.get_fruits()->at(2) == fruit({300,400},false,1));
    CHECK(set.get_fruits()->at(3) == fruit({300,336},false,2));

    set.add_fruits(fruit({500,335},true,1));
    set.add_fruits(fruit({500,400},true,2));
    set.group_overlapped();
    CHECK(set.get_fruits()->at(4) == fruit({500,335},true,1));
    CHECK(set.get_fruits()->at(5) == fruit({500,400},true,2));
}


TEST_CASE("Fruit Next")
{
    fruit subject = fruit({100,400},true,1);

    subject = subject.next(1);
    CHECK(subject == fruit({100,410},true,1));

    subject = subject.next(1);
    CHECK(subject == fruit({100,434},true,1));

    subject = subject.next(1);
    CHECK(subject == fruit({100,472},true,1));

    subject = subject.next(1);
    CHECK(subject == fruit({100,524},true,1));
}


TEST_CASE("Find Height"){
    Model m;
    fruit_sets set = m.get_set();

    set.add_fruits(fruit({100,400},true,1));
    set.add_fruits(fruit({100,276},false,1));
    set.add_fruits(fruit({100,336},true,2));
    CHECK(set.find_height() == 251);

    set.clear_fruits();
    set.add_fruits(fruit({100,400},true,1));
    CHECK(set.find_height() == 800);

    set.clear_fruits();
    set.add_fruits(fruit({100,336},true,2));
    set.add_fruits(fruit({100,276},false,1));
    CHECK(set.find_height() == 800);

    set.clear_fruits();
    CHECK(set.find_height() == 800);

}

TEST_CASE("Get Max Tier"){
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({100,100},true,2));
    set.add_fruits(fruit({120,120},true,7));
    set.add_fruits(fruit({120,140},false,6));
    CHECK(set.find_max_tier() == 7);

}

TEST_CASE("merge w/o reposition")
{
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({100,100},true,2));
    set.add_fruits(fruit({120,120},true,2));
    set.merge();
    CHECK(set.get_fruits()->at(0) == fruit({110,110},true,3));
    CHECK(set.get_score() == 2);
}

TEST_CASE("merge and repositioning when touching LEFT side")
{
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({10,100},true,2));
    set.add_fruits(fruit({20,120},true,2));
    set.merge();
    CHECK(set.get_fruits()->at(0) == fruit({55,110},true,3));
}

TEST_CASE("merge and repositioning when touching RIGHT side")
{
    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({600,100},true,2));
    set.add_fruits(fruit({600,120},true,2));
    set.merge();
    CHECK(set.get_fruits()->at(0) == fruit({544,110},true,3));
}

TEST_CASE("all_overlap: returns the height of the highest circle that is"
          "overlapping with the vector")
{
    Model model;
    fruit a = fruit({55,110},true,3);
    fruit b = fruit({400,400},true,3);
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({65,110},true,2));
    set.add_fruits(fruit({500,120},true,2));
    CHECK(set.all_overlapped(a) == 110);
    CHECK(set.all_overlapped(b) == 0);
}

TEST_CASE("all overlapped"){
    Model model;
    fruit a = fruit({55,110},true,3);
    fruit b = fruit({400,400},true,3);
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({65,110},true,2));
    set.add_fruits(fruit({500,120},true,2));
    CHECK(set.all_overlapped(a) == 110);
    CHECK(set.all_overlapped(b) == 0);
}

TEST_CASE("On Frame: Generic Testing"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({65,110},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,120},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,144},true,2));

}

TEST_CASE("On Frame: Dead ball"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({65,760},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,761},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,761},false,2));
}

TEST_CASE("On Frame: Floating Ball"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({65,110},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,110},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,120},true,2));
}

TEST_CASE("On Frame: With Merge"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({65,110},true,2));
    set->add_fruits(fruit({65,130},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,125},true,3));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,135},true,3));

}

TEST_CASE("On Frame: With Group Overlapped"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({65,680},true,1));
    set->add_fruits(fruit({65,761},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,690},true,1));
    CHECK(set->get_fruits()->at(1)==fruit({65,761},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({65,697},false,1));
}


TEST_CASE("On Frame: All test"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({540,700},true,2));
    set->add_fruits(fruit({558,720},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({544,720},true,3));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({544,730},true,3));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({544,746},false,3));
}

TEST_CASE("On Frame: All test 2"){
    Model model;

    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({550,600},true,2));
    set->add_fruits(fruit({550,740},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({550,610},true,2));
    CHECK(set->get_fruits()->at(1)==fruit({550,740},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({550,634},true,2));
    CHECK(set->get_fruits()->at(1)==fruit({550,750},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({550,672},true,2));
    CHECK(set->get_fruits()->at(1)==fruit({550,761},false,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({544,742},true,3));

}

TEST_CASE("On frame: Chain reaction"){

    Model model;
    fruit_sets *set = model.get_set_ptr();
    set->add_fruits(fruit({550,500},true,2));
    set->add_fruits(fruit({550,640},false,2));
    set->add_fruits(fruit({530,746},false,3));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({550,510},true,2));
    CHECK(set->get_fruits()->at(1)==fruit({550,640},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({550,534},true,2));
    CHECK(set->get_fruits()->at(1)==fruit({550,650},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({550,572},true,2));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({544,637},false,3));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({529,691},true,4));
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({529,701},true,4));
    model.on_frame(1);
    model.on_frame(1);
    CHECK(set->get_fruits()->at(0)==fruit({529,731},false,4));

}




TEST_CASE("Reposition"){

    Model model;
    fruit subject = fruit ({0,110},true,3);
    model.get_set().reposition(subject);
    CHECK(subject == fruit({55,110},true,3));

    fruit subject2 = fruit ({600,110},true,4);
    model.get_set().reposition(subject2);
    CHECK(subject2 == fruit({529,110},true,4));

    fruit subject3 = fruit ({300,800},true,7);
    model.get_set().reposition(subject3);
    CHECK(subject3 == fruit({300,685},true,7));
}

TEST_CASE("float check")
{

    Model model;
    fruit_sets set = model.get_set();
    set.add_fruits(fruit({500,120},false,2));
    set.add_fruits(fruit({65,110},false,2));
    set.add_fruits(fruit({56,120},false,3));
    set.float_check();
    //not overlapping: false -> true
    CHECK(set.get_fruits()->at(0).get_live());

    //overlaps but at the bottom
    //upper: false -> false
    CHECK_FALSE(set.get_fruits()->at(1).get_live());
    //lower: false -> true
    CHECK(set.get_fruits()->at(2).get_live());

    //touches edge: false -> false
    set.add_fruits(fruit({0,50},false,2));
    set.add_fruits(fruit({599,50},false,2));
    set.add_fruits(fruit({200,799},false,2));
    set.add_fruits(fruit({0,799},false,2));
    set.float_check();
    CHECK_FALSE(set.get_fruits()->at(3).get_live());
    CHECK_FALSE(set.get_fruits()->at(4).get_live());
    CHECK_FALSE(set.get_fruits()->at(5).get_live());
    CHECK_FALSE(set.get_fruits()->at(6).get_live());


}



