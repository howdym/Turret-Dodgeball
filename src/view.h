//
// Created by marcj on 3/9/2019.
//

#ifndef FINAL_PROJECT_VIEW_H
#define FINAL_PROJECT_VIEW_H

#endif //FINAL_PROJECT_VIEW_H

#pragma once

//#include <ge211.h>
//do we need this?

#include "model.h"
#include "../.eecs211/lib/ge211/include/ge211_sprites.h"

#include <string>

extern ge211::Color const white_color, player_red_color, ball_red_color, player_blue_color, ball_blue_color;
extern ge211::Color const ball_red_color_1, ball_blue_color_1;
extern ge211::Color const green_1, green_2, green_3, green_4, green_5;
extern ge211::Dimensions const horidim, vertidim;


class View
{
public:

    View(Model &);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set&) const;

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;


private:
    Model const& model_;

    ge211::Circle_sprite const
            red_player_ {player_radius, player_red_color};

    ge211::Circle_sprite const
            blue_player_ {player_radius, player_blue_color};

    ge211::Circle_sprite const
            ball {ball_radius, white_color};

    ge211::Circle_sprite const
            red_ball_0 {ball_radius, ball_red_color};

    ge211::Circle_sprite const
            blue_ball_0 {ball_radius, ball_blue_color};

    ge211::Circle_sprite const
            blue_ball_1 {ball_radius, ball_blue_color_1};

    ge211::Circle_sprite const
            red_ball_1 {ball_radius, ball_red_color_1};

    ge211::Rectangle_sprite const
            horiz_bound_ {horidim, white_color};
    ge211::Rectangle_sprite const
            verti_bound_ {vertidim, white_color};

    ge211::Rectangle_sprite const
            turret_1 {{turret_size, turret_size}, green_1};
    ge211::Rectangle_sprite const
            turret_2 {{turret_size, turret_size}, green_2};
    ge211::Rectangle_sprite const
            turret_3 {{turret_size, turret_size}, green_3};
    ge211::Rectangle_sprite const
            turret_4 {{turret_size, turret_size}, green_4};
    ge211::Rectangle_sprite const
            turret_5 {{turret_size, turret_size}, green_5};



    ge211::Font sans{"sans.ttf", 24};
    ge211::Text_sprite mutable blue_lives_sprite_  {"hello world", sans};
    ge211::Text_sprite mutable red_lives_sprite_  {"hello world", sans};
    ge211::Text_sprite mutable blue_money_sprite_  {"hello world", sans};
    ge211::Text_sprite mutable red_money_sprite_  {"hello world", sans};


    ge211::Font big_sans{"sans.ttf", 48};
    ge211::Text_sprite mutable blue_win  {"BLUE VICTORY", big_sans};
    ge211::Text_sprite mutable red_win  {"RED VICTORY", big_sans};

    ge211::Text_sprite lives_sprite_text  {"Lives:", sans};
    ge211::Text_sprite money_sprite_text  {"Money:", sans};
};