//
// Created by marcj on 3/6/2019.
//

#ifndef FINAL_PROJECT_CONTROLLER_H
#define FINAL_PROJECT_CONTROLLER_H

#endif //FINAL_PROJECT_CONTROLLER_H

#pragma once

// #include <ge211.h>
// Need to add later on

#include "model.h"
#include "view.h"
#include "../.eecs211/lib/ge211/include/ge211_base.h"

class Controller : public ge211::Abstract_game
{
public:

    Controller();

protected:

    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;
    void on_key_up(ge211::Key key) override;
    void on_key_down(ge211::Key) override;
    void on_frame(double) override;

private:

    Model            model_;
    View             view_;
    bool bd_ = false;
    bool ru_ = false;
    bool br_ = false;
    bool bl_ = false;
    bool bu_ = false;
    bool rl_ = false;
    bool rr_ = false;
    bool rd_ = false;
};