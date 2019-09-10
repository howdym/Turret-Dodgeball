#include "model.h"

Character::Character(Player p, ge211::Position pos)
        : type_(p)
        , char_location_(pos)
{
    lives_ = live_count_;
    money_ = initial_money_;
}

Ball::Ball(Player p, ge211::Position pos, int speed, int x, int pn)
        : type_(p)
        , ball_center_(pos)
        , velocity_((x % (speed / 2) + (speed / 2)) * pn, x % (speed / 2) - (speed / 4))
{
    bounce_count_ = 0;
}

Ball::Ball(Player p, ge211::Position pos, ge211::Position v)
        : type_(p)
        , ball_center_(pos)
        , velocity_(v)
{
    bounce_count_ = 0;
}

Ball::Ball(Player p, ge211::Position pos, ge211::Position v, int bounce_count)
        : type_(p)
        , ball_center_(pos)
        , velocity_(v)
{
    bounce_count_ = bounce_count;
}

Turret::Turret(Player p, ge211::Position pos)
        : type_(p)
        , turret_location_(pos)
{
    level_ = 1;
    fire_speed_ = initial_fire_speed_;
    fire_rate_ = initial_fire_rate_;
    cost_ = turret_cost_inc_;
}

Model::Model()
        : red_(Player::red, {width_ / 4, height_ / 2})
        , blue_(Player::blue, {width_ * 3 / 4, height_ / 2})
{
    list_of_balls_ = {};
    list_of_turrets_ = {};
    winner_ = Player::neither;
}

ge211::Position Character::top_left() const {
    int x = char_location_.x - player_radius;
    int y = char_location_.y - player_radius;
    return {x,y};
}

ge211::Position Character::get_position() const {
    return char_location_;
}

Player Character::get_player() const {
    return type_;
}

int Character::get_lives() const {
    return lives_;
}

int Character::get_money() const {
    return money_;
}

void Character::change_money(int x) {
    money_ += x;
}

void Character::change_lives() {
    lives_--;
}

void Character::move_left() {
    if (type_ == Player::red) {
        char_location_.x = std::max(char_location_.x - 1, player_radius);
    } else {
        char_location_.x = std::max(char_location_.x - 1, width_ / 2 + player_radius);
    }
}

void Character::move_right() {
    if (type_ == Player::red) {
        char_location_.x = std::min(char_location_.x + 1, width_ / 2 - player_radius);
    } else {
        char_location_.x = std::min(char_location_.x + 1, width_ - player_radius);
    }
}

void Character::move_up() {
    char_location_.y = std::max(char_location_.y - 1, player_radius);
}

void Character::move_down() {
    char_location_.y = std::min(char_location_.y + 1, height_ - player_radius);
}



ge211::Position Ball::top_left() const {
    int x = ball_center_.x - ball_radius;
    int y = ball_center_.y - ball_radius;
    return {x,y};
}

ge211::Position Ball::bottom_right() const {
    int x = ball_center_.x + ball_radius;
    int y = ball_center_.y + ball_radius;
    return {x,y};
}

int Ball::get_bounce_count() const {
    return bounce_count_;
}

ge211::Position Ball::get_position() const {
    return ball_center_;
}

ge211::Position Ball::get_velocity() const {
    return velocity_;
}

Player Ball::get_player() const {
    return type_;
}

void Ball::move_ball() {
    ball_center_.x = ball_center_.x + velocity_.x;
    ball_center_.y = ball_center_.y + velocity_.y;
}

bool Ball::hit_top_wall() const {
    ge211::Position top_pos = top_left();
    return top_pos.y <= 0;
}

bool Ball::hit_bottom_wall() const {
    ge211::Position bottom_pos = bottom_right();
    return bottom_pos.y >= height_;
}

bool Ball::hit_left_wall() const {
    ge211::Position left_pos = top_left();
    return left_pos.x <= 0;
}

bool Ball::hit_right_wall() const {
    ge211::Position right_pos = bottom_right();
    return right_pos.x >= width_;
}

void Ball::bounce_x() {
    velocity_.x = velocity_.x * -1;
    bounce_count_++;
}

void Ball::bounce_y() {
    velocity_.y = velocity_.y * -1;
    bounce_count_++;
};

bool Ball::hit_character(Character c) const {
    if (c.get_player() == get_player()) {
        return false;
    }
    ge211::Position char_pos = c.get_position();
    int dist = (char_pos.x - ball_center_.x) * (char_pos.x - ball_center_.x) + (char_pos.y - ball_center_.y) * (char_pos.y - ball_center_.y);
    int threshold = (player_radius + ball_radius) * (player_radius + ball_radius);
    return threshold >= dist;
}

bool operator==(Ball const& b1, Ball const& b2)
{
    return b1.get_position() == b2.get_position() && b1.get_player() == b2.get_player() &&
           b1.get_bounce_count() == b2.get_bounce_count() && b1.get_velocity() == b2.get_velocity();
}

bool operator!=(Ball const& b1, Ball const& b2)
{
    return !(b1 == b2);
}

ge211::Position Turret::get_position() const {
    return turret_location_;
}

Player Turret::get_player() const {
    return type_;
}

int Turret::get_level() const {
    return level_;
}

int Turret::get_cost() const {
    return cost_;
}

int Turret::get_fire_speed() const {
    return fire_speed_;
}

int Turret::get_fire_rate() const {
    return fire_rate_;
}

void Turret::level_up() {
    cost_ = cost_ + turret_cost_inc_ * level_;
    level_++;
    fire_speed_ = fire_speed_ + speed_inc_;
}

bool Turret::hit_character(Character c) const {
    if (c.get_player() != get_player()) {
        return false;
    }
    ge211::Position char_pos = c.get_position();
    int dist = (char_pos.x - turret_location_.x) * (char_pos.x - turret_location_.x) +
               (char_pos.y - turret_location_.y) * (char_pos.y - turret_location_.y);
    int threshold = (player_radius + turret_size / 2) * (player_radius + turret_size / 2);
    return threshold >= dist;
}

bool operator==(Turret const& b1, Turret const& b2)
{
    return b1.get_position() == b2.get_position() && b1.get_player() == b2.get_player() &&
           b1.get_fire_speed() == b2.get_fire_speed() && b1.get_fire_rate() == b2.get_fire_rate() &&
           b1.get_cost() == b2.get_cost() && b1.get_level() == b2.get_level();
}

bool operator!=(Turret const& b1, Turret const& b2)
{
    return !(b1 == b2);
}

Player Model::get_winner() const {
    return winner_;
}

std::vector<Ball> Model::get_ball() const {
    return list_of_balls_;
}

std::vector<Turret> Model::get_turret() const {
    return list_of_turrets_;
}

void Model::add_turret(Turret t) {
    list_of_turrets_.push_back(t);
}

void Model::update(int x) {
    update_balls();
    fire_all_turrets(x);
    game_over();
}

void Model::update_turret(Character c) {
    for (int i = 0; i < list_of_turrets_.size(); i++) {
        if (list_of_turrets_[i].hit_character(c) && list_of_turrets_[i].get_player() == c.get_player()) {
            Turret t = list_of_turrets_[i];
            if (t.get_level() != max_level_ && t.get_cost() <= c.get_money()) {
                c.change_money(-1 * t.get_cost());
                if (c.get_player() == Player::blue) {
                    blue_ = c;
                } else {
                    red_ = c;
                }
                t.level_up();
            }
            list_of_turrets_[i] = t;
        }
    }
}

bool Model::check_touching(Character c) {
    for (Turret t : list_of_turrets_) {
        if (t.hit_character(c) && t.get_player() == c.get_player()) {
            return true;
        }
    }
    return false;
}

void Model::destroy_ball(Ball b) {
    for (int i = 0; i < list_of_balls_.size(); i++) {
        if (list_of_balls_[i] == b) {
            std::swap(list_of_balls_[i], list_of_balls_.back());
            list_of_balls_.pop_back();
        }
    }
}

void Model::update_balls() {
    for (int i = 0; i < list_of_balls_.size(); i++) {
        Ball future_ball = list_of_balls_[i];

        //checks the future position of the ball
        future_ball.move_ball();


        //if collision against player: give one player money and hurt the other, destroy ball
        if (future_ball.hit_character(red_)) {
            destroy_ball(list_of_balls_[i]);
            red_.change_lives();
            blue_.change_money(hit_char_earnings_);
        } else if (future_ball.hit_character(blue_)) {
            destroy_ball(list_of_balls_[i]);
            blue_.change_lives();
            red_.change_money(hit_char_earnings_);
        }

            //otherwise, check for collision with top or bottom - reflects ball and increments bounce_count
        else {
            if (future_ball.hit_bottom_wall() || future_ball.hit_top_wall()) {
                list_of_balls_[i].bounce_y();
            }

            //still check for collision with side too - gives a player money, reflects ball, and increments bounce_count
            if (future_ball.hit_left_wall()) {
                list_of_balls_[i].bounce_x();
                red_.change_money(hit_side_earnings_);
            }
            if (future_ball.hit_right_wall()) {
                list_of_balls_[i].bounce_x();
                blue_.change_money(hit_side_earnings_);
            }


            //finally checks if bounce_count is less than 2; updates position of ball, otherwise destroys the ball
            if (list_of_balls_[i].get_bounce_count() < 2) {
                list_of_balls_[i].move_ball();
            } else {
                destroy_ball(list_of_balls_[i]);
            }
        }
    }
}

void Model::fire_turret(Turret t, int x) {
    if (t.get_fire_rate() % initial_fire_rate_ == 0) {
        int i = 1;
        if (t.get_player() == Player::blue) {
            i = i * -1;
        }
        Ball a(t.get_player(), t.get_position(), t.get_fire_speed(), x, i);
        list_of_balls_.push_back(a);
    }
}

// Have the controller do the random in on_frame
void Model::fire_all_turrets(int x) {
    for (int i = 0; i < list_of_turrets_.size(); i++) {
        list_of_turrets_[i].decrement_time();
        fire_turret(list_of_turrets_[i], x);
    }
}

// Red will be winner if tie
void Model::game_over() {
    if (blue_.get_lives() == 0) {
        winner_ = Player::red;
    } else if (red_.get_lives() == 0) {
        winner_ = Player::blue;
    } else {
        winner_ = Player::neither;
    }
}

ge211::Position Turret::top_left() const {
    int x = turret_location_.x - turret_size / 2;
    int y = turret_location_.y - turret_size / 2;
    return {x,y};
}

void Turret::decrement_time() {
    fire_rate_++;
}