//
// Created by marcj on 3/6/2019.
//

#include "controller.h"

using namespace ge211;

Controller::Controller()
        : model_()
        , view_(model_)
{}

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites);
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_key_up(ge211::Key key) {
    if (key == ge211::Key::code(' ')) {
        if (model_.check_touching(model_.red_)) {
            model_.update_turret(model_.red_);
        } else {
            if (model_.red_.get_money() >= turret_cost_inc_) {
                model_.add_turret(Turret(Player::red, model_.red_.get_position()));
                model_.red_.change_money(-1 * turret_cost_inc_);
            }
        }
    }
    if (key == ge211::Key::code('/')) {
        if (model_.check_touching(model_.blue_)) {
            model_.update_turret(model_.blue_);
        } else {
            if (model_.blue_.get_money() >= turret_cost_inc_) {
                model_.add_turret(Turret(Player::blue, model_.blue_.get_position()));
                model_.blue_.change_money(-1 * turret_cost_inc_);
            }
        }
    }
    if (key == ge211::Key::code('w')) {
        ru_ = false;
    }
    if (key == ge211::Key::code('a')) {
        rl_ = false;
    }
    if (key == ge211::Key::code('s')) {
        rd_ = false;
    }
    if (key == ge211::Key::code('d')) {
        rr_ = false;
    }
    if (key == ge211::Key::up()) {
        bu_ = false;
    }
    if (key == ge211::Key::right()) {
        br_ = false;
    }
    if (key == ge211::Key::down()) {
        bd_ = false;
    }
    if (key == ge211::Key::left()) {
        bl_ = false;
    }
}

void Controller::on_key_down(ge211::Key key) {
    if (key == ge211::Key::code('w')) {
        ru_ = true;
    }
    if (key == ge211::Key::code('a')) {
        rl_ = true;
    }
    if (key == ge211::Key::code('s')) {
        rd_ = true;
    }
    if (key == ge211::Key::code('d')) {
        rr_ = true;
    }
    if (key == ge211::Key::up()) {
        bu_ = true;
    }
    if (key == ge211::Key::right()) {
        br_ = true;
    }
    if (key == ge211::Key::down()) {
        bd_ = true;
    }
    if (key == ge211::Key::left()) {
        bl_ = true;
    }
}

void Controller::on_frame(double) {
    if (ru_) {
        model_.red_.move_up();
    }
    if (rl_) {
        model_.red_.move_left();
    }
    if (rd_) {
        model_.red_.move_down();
    }
    if (rr_) {
        model_.red_.move_right();
    }
    if (bu_) {
        model_.blue_.move_up();
    }
    if (br_) {
        model_.blue_.move_right();
    }
    if (bd_) {
        model_.blue_.move_down();
    }
    if (bl_) {
        model_.blue_.move_left();
    }
    if (model_.get_winner() == Player::neither) {
        model_.update(rand());
    }

}