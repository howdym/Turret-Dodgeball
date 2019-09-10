#pragma once

//#include <ge211.h>
#include "../.eecs211/lib/ge211/include/ge211_base.h"
#include "player.h"

//
// Model constants
//

int const player_radius = 20;
int const ball_radius = 5;
int const turret_size = 50;
int const width_ = 800;
int const height_ = 400;
int const hit_char_earnings_ = 100;
int const hit_side_earnings_ = 50;
int const initial_money_ = 200;
int const live_count_ = 5;
int const initial_fire_speed_ = 10;
int const initial_fire_rate_ = 300;
int const turret_cost_inc_ = 100;
int const speed_inc_ = 2;
int const max_level_ = 5;


//
// Model classes
//

// Properties of a character that each of the players will be controlling
class Character {

    //
    // Private members
    //

    Player type_; // red or blue
    ge211::Position char_location_;
    int lives_;
    int money_;

public:

    explicit Character(Player, ge211::Position);

    // Returns the position of the top-left corner of the ball's "bounding
    // box", meaning the smallest rectangle in which is can be enclosed.
    // This is useful to the UI because sprites are positioned based on
    // their top-left corners.
    ge211::Position top_left() const;

    // Gets the position of the center of the character
    ge211::Position get_position() const;

    // Gets the player that controls the character
    Player get_player() const;

    // Gets how much money the character has
    int get_money() const;

    // Gets how many lives the character has left
    int get_lives() const;

    // Increment the money of a character by a given amount
    void change_money(int x);

    // Decrement the lives of a character by one
    void change_lives();

    // Move the sprite left
    void move_left();

    // Move the sprite right
    void move_right();

    // Move the sprite up
    void move_up();

    // Move the sprite down
    void move_down();
};

// Properties of one ball
// Constructor Specifications:
// 1. Player, Position, and Speed (Player, ge211:Position, int)
// 2. Player, Position, and Speed (Player, ge211:Position, ge211::Position)
// 3. Player, Position, Speed, and Bounce Count (Player, ge211::Position, ge211::Position, int)
class Ball {

    //
    // Private members
    //

    Player type_; // red or blue, Player enum comes from another file
    int bounce_count_ = 0;
    ge211::Position ball_center_;
    ge211::Position velocity_;

public:

    Ball(Player p, ge211::Position pos, int speed, int x, int pn);

    Ball(Player p, ge211::Position pos, ge211::Position speed);

    Ball(Player p, ge211::Position pos, ge211::Position speed, int bounce_count);

    // Returns the position of the top-left corner of the ball's "bounding
    // box", meaning the smallest rectangle in which is can be enclosed.
    // This is useful to the UI because sprites are positioned based on
    // their top-left corners.
    ge211::Position top_left() const;

    // Returns the position of the bottom-right corner of the ball's "bounding
    // box", meaning the smallest rectangle in which is can be enclosed.
    ge211::Position bottom_right() const;

    // Gets the number of times the ball has had contact with a wall
    int get_bounce_count() const;

    // Gets the position of the center of the ball
    ge211::Position get_position() const;

    // Gets the velocity of the ball
    ge211::Position get_velocity() const;

    // Gets the player whose turret fired the ball
    Player get_player() const;

    // Increments the position of the ball by the velocity
    // Equivalence of next() in brick out
    void move_ball();

    // Check to see if ball had contact with the top and bottom walls.
    bool hit_top_wall() const;
    bool hit_bottom_wall() const;

    // Check to see if ball had contact with the left and right walls.
    bool hit_left_wall() const;
    bool hit_right_wall() const;

    // Will increment bounce_count by 1 and change x-velocity to negative of what it originally was.
    void bounce_x();

    // Will increment bounce_count by 1 and change y-velocity to negative of what it originally was.
    void bounce_y();

    // Check to see if ball had contact with the opposing team.
    // Friendly fire is prohibited
    bool hit_character(Character) const;

};

// Properties of a turret that the players will be placing down
// Constructor: player type, turret location
class Turret {

    //
    // Private members
    //
    Player type_; // Red or blue
    int level_;
    int fire_speed_;
    int fire_rate_;
    int cost_;
    ge211::Position turret_location_;

public:

    void decrement_time();

    Turret(Player, ge211::Position);

    // Gets the position of the turret
    ge211::Position get_position() const;

    // Gets the player that owns the turret
    Player get_player() const;

    // Gets the level of the turret
    int get_level() const;

    // Gets the cost of the turret
    int get_cost() const;

    // Gets the firing speed of the turret
    int get_fire_speed() const;

    // Gets the firing rate of the turret
    int get_fire_rate() const;

    // Level up a turret
    void level_up();

    // Check if turret is touching character
    bool hit_character(Character c) const;

    ge211::Position top_left() const;
};

class Model {

    //
    // Private members
    //

public:

    Character red_;
    Character blue_;

    explicit Model();

    // Gets the winner of the game
    Player get_winner() const;

    // Gets the list of balls that are active in the game
    std::vector<Ball> get_ball() const;

    // Gets the list of turrets that are active in the game
    std::vector<Turret> get_turret() const;

    // Adds turret to board
    void add_turret(Turret);

    // Checks if a turret is touching character
    // Update the turret
    // Upgrade the given turret and decrease player's money
    // Checks if turret is max level before upgrading
    void update_turret(Character c);

    // Checks if a turret is touching character
    bool check_touching(Character c);

    // Updates the game to check if the balls made contact with anything
    // and if turrets are supposed to fire.
    // Also checks and sets game over if game is over.
    void update(int x);

private:
    std::vector<Ball> list_of_balls_;
    std::vector<Turret> list_of_turrets_;
    Player winner_;
    // For Ball:

    // Destroy a ball
    void destroy_ball(Ball);

    // Updates/moves every ball in list_of_balls_ and checks if they made contact with any walls
    // Destroy ball if bounce_count_ is 2
    // If contact with character (check first)
    // Will decrease lives by 1 of that player and ball will be destroyed
    // Will also increment the money amount of the player who shot that ball
    // Destroy ball
    // If contact side walls
    // Will increment bounce_count by 1 and change x-velocity to negative of what it originally was.
    // Will also increment the money amount of the player who had the ball bounce on their side of the field
    // If contact top or bottom wall
    // Will increment bounce_count by 1 and change y-velocity to negative of what it originally was
    void update_balls();

    // For turret:

    // Fire a ball by the rate given
    // Updates time for next shot
    // Won't fire if not time yet
    void fire_turret(Turret t, int x);

    // Check each turret to see if they need to fire a ball
    void fire_all_turrets(int);

    // Check if game is over
    void game_over();

    // Test access
    friend class Test_access ;
};