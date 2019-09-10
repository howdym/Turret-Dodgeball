//
// Created by marcj on 3/9/2019.
//

#include "view.h"

using namespace ge211;

// constants for drawing the sprites:
ge211::Color const white_color   {255, 255, 255};
ge211::Color const player_red_color (255, 0, 0);
ge211::Color const player_blue_color (0,0 , 255);
ge211::Color const ball_red_color (255, 0 , 0);
ge211::Color const ball_red_color_1 (122, 0 , 0);
ge211::Color const ball_blue_color (0,0 , 255);
ge211::Color const ball_blue_color_1 (0, 0 , 122);

ge211::Color const green_1 (0, 55 , 0);
ge211::Color const green_2 (0, 105 , 0);
ge211::Color const green_3 (0, 155 , 0);
ge211::Color const green_4 (0, 205 , 0);
ge211::Color const green_5 (0, 255 , 0);

ge211::Dimensions const horidim {width_, 3};
ge211::Dimensions const vertidim {3, height_};


View::View(Model &model)
        : model_(model)
// You may want to add sprite initialization here
{ }

void View::draw(ge211::Sprite_set& set) const
{
    //wot is just a position initializer
    ge211::Position wot (0,0);


    //endgame screen
    wot.y = 30;
    if (model_.get_winner() == Player::blue){
        wot.x = width_/4 * 3 - 20;
        set.add_sprite(blue_win, wot, 5);
    }
    if (model_.get_winner() == Player::red){
        wot.x = width_/4 - 20;
        set.add_sprite(red_win, wot, 5);
    }

    wot.x = 0;
    wot.y = 0;
    //draw boundaries of each player's area
    set.add_sprite(horiz_bound_, wot, 1);
    set.add_sprite(verti_bound_, wot, 1);

    wot.y = height_ - 3;
    set.add_sprite(horiz_bound_, wot, 1);

    wot.y = 0;
    wot.x = width_/2 - 1;
    set.add_sprite(verti_bound_, wot, 1);

    wot.x = width_ - 3;
    set.add_sprite(verti_bound_, wot, 1);

    //draw the stationary text interface


        //red lives
    int my_value = model_.red_.get_lives();

    red_lives_sprite_.reconfigure(
            ge211::Text_sprite::Builder(sans) << my_value);
    wot.x = width_/4;
    wot.y = height_ + 10;
    set.add_sprite(red_lives_sprite_, wot, 10);

        //blue lives
    my_value = model_.blue_.get_lives();

    blue_lives_sprite_.reconfigure(
            ge211::Text_sprite::Builder(sans) << my_value);
    wot.x = width_/4 * 3;
    wot.y = height_ + 10;
    set.add_sprite(blue_lives_sprite_, wot, 10);

        //text for lives and money
    wot.x = width_/4 - 100;
    wot.y = height_ + 10;
    set.add_sprite(lives_sprite_text, wot, 10);
    wot.x = width_/4 * 3 - 100;
    set.add_sprite(lives_sprite_text, wot, 10);

    wot.y = height_ + 30;
    set.add_sprite(money_sprite_text, wot, 10);
    wot.x = width_/4 - 100;
    set.add_sprite(money_sprite_text, wot, 10);


        //red money
    my_value = model_.red_.get_money();

    red_money_sprite_.reconfigure(
            ge211::Text_sprite::Builder(sans) << my_value);
    wot.x = width_/4;
    wot.y = height_ + 30;
    set.add_sprite(red_money_sprite_, wot, 10);

        //blue money
    my_value = model_.blue_.get_money();

    blue_money_sprite_.reconfigure(
            ge211::Text_sprite::Builder(sans) << my_value);
    wot.x = width_/4 * 3;
    wot.y = height_ + 30;
    set.add_sprite(blue_money_sprite_, wot, 10);


    if (model_.get_winner() == Player::neither || model_.get_winner() == Player::red) {
        //draw red player
        wot = model_.red_.top_left();

        set.add_sprite(red_player_, wot, 3);
    }


    //draw blue player

    if (model_.get_winner() == Player::neither || model_.get_winner() == Player::blue) {
        wot = model_.blue_.top_left();
        set.add_sprite(blue_player_, wot, 3);
    }

    //draw turrets
    // doesn't account for change in level

    if (model_.get_winner() == Player::neither) {
        for (Turret t : model_.get_turret()) {


            if (t.get_level() == 1) {
                set.add_sprite(turret_1, t.top_left(), 2);
            }
            if (t.get_level() == 2) {
                set.add_sprite(turret_2, t.top_left(), 2);
            }
            if (t.get_level() == 3) {
                set.add_sprite(turret_3, t.top_left(), 2);
            }
            if (t.get_level() == 4) {
                set.add_sprite(turret_4, t.top_left(), 2);
            }
            if (t.get_level() == 5) {
                set.add_sprite(turret_5, t.top_left(), 2);
            }
        }
    }

    //draw balls
    for (Ball b : model_.get_ball()) {
        if (b.get_player() == Player::red) {
            if (b.get_bounce_count() == 0) {
                set.add_sprite(red_ball_0, b.top_left(), 3);
            } else {
                set.add_sprite(red_ball_1, b.top_left(), 3);
            }
        } else if (b.get_player() == Player::blue) {
            if (b.get_bounce_count() == 0) {
                set.add_sprite(blue_ball_0, b.top_left(), 3);
            } else {
                set.add_sprite(blue_ball_1, b.top_left(), 3);
            }
        }
    }





}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    Dimensions ans;
    ans.width = width_;
    ans.height = height_ + 100;
    return ans;
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Dodgeball War";
}