#include "model.h"
#include <catch.h>

TEST_CASE("example test")
{
    CHECK( 1 + 1 == 2 );
}

TEST_CASE("ball to human")
{
    Model m;
    Ball b(Player::red, {0, 0}, {1, 0}); // constructor takes in player, position, and velocity
    Test_access t{m};
    t.get_ball().clear();

    // Put the ball in play
    t.get_ball().push_back(b);

    // Initialize the player's locations
    t.get_blue() = Character{Player::blue, {32, 0}, 5, 200};
    t.get_red() = Character{Player::red, {32, 0}, 5, 200};

    // Use to check if the helper functions work
    Test_access oldt{m};
    Test_access oldt2{m};

    // Updates the motion of the ball and checks/adjusts if there is any contact
    t.update_balls();

    // Manually update using the helper functions
    oldt.get_ball()[0].move_ball();
    oldt2.get_ball()[0].move_ball();

    // The ball didn't hit the character
    CHECK_FALSE(oldt.get_ball()[0].hit_character());
    CHECK_FALSE(oldt2.get_ball()[0].hit_character());
    CHECK_FALSE(oldt.get_blue().got_hit(oldt.get_ball()));
    CHECK_FALSE(oldt2.get_blue().got_hit(oldt2.get_ball()));

    // Check if the ball actually moved
    ge211::Position npos = oldt.get_ball()[0].get_position();
    ge211::Position npos2 = oldt2.get_ball()[0].get_position();
    CHECK(npos.x == 1);
    CHECK(npos.y == 0);
    CHECK(npos2.x == 1);
    CHECK(npos2.y == 0);

    // Nothing changes because no contact
    CHECK(t.get_blue().lives_ == 5); // Let's say for now that default lives is 5
    CHECK(t.get_red().money_ == 200); // Let's say for now that default money is 200

    // Updates the motion of the ball and checks/adjusts if there is any contact
    t.update_balls();

    // Ball hits blue Character, so their lives will go down
    // Ball does touch red Character, but friendly fire is prohibited
    // Their lives will not change, but they will gain money (let's say 50 for now)
    CHECK(t.get_blue().lives_ == 4);
    CHECK(t.get_red().money_ == 250);

    // Manually update using the helper functions
    oldt.get_ball()[0].move_ball();
    oldt2.get_ball()[0].move_ball();

    // Check if the ball actually moved
    npos = oldt.get_ball()[0].get_position();
    npos2 = oldt2.get_ball()[0].get_position();
    CHECK(npos.x == 2);
    CHECK(npos.y == 0);
    CHECK(npos2.x == 2);
    CHECK(npos2.y == 0);

    // The ball did hit the character
    CHECK(oldt.get_ball()[0].hit_character());
    CHECK(oldt2.get_ball()[0].hit_character());
    CHECK(oldt.get_blue().got_hit(oldt.get_ball()));
    CHECK(oldt2.get_blue().got_hit(oldt2.get_ball()));

    // Lives and money should change as well
    CHECK(oldt.get_blue().lives_ == 4);
    CHECK(oldt.get_red().money_ == 250);
    CHECK(oldt2.get_blue().lives_ == 4);
    CHECK(oldt2.get_red().money_ == 250);

    // Check if ball disappears
    CHECK(t.get_ball().size() == 0);
    CHECK(oldt.get_ball().size() == 0);
    CHECK(oldt2.get_ball().size() == 0);
}

TEST_CASE("Ball to left wall") {
    // Assuming left wall is part of red side, they will gain currency when the ball hits the left side

    Model m;
    Ball b(Player::red, {6, 0}, {-1, 0});
    Test_access t{m};
    t.get_ball().clear();

    // Put the ball in play
    t.get_ball().push_back(b);

    // Use to check if the helper functions work
    Test_access oldt{m};

    // Updates the motion of the ball and checks/adjusts if there is any contact
    t.update_balls();

    // It shouldn't be hitting the wall right now
    CHECK_FALSE(oldt.get_ball()[0].hit_left_wall());

    // Manually update using the helper functions
    oldt.get_ball()[0].move_ball();

    // Check to see if actually registered that it hit the wall
    CHECK(oldt.get_ball()[0].hit_left_wall());

    // Both balls should have a reversed x velocity and red should gain money (let's say 100)
    // Both balls should also have a bounce_count of 1
    CHECK(t.get_ball()[0].velocity().x = 1);
    CHECK(t.get_ball()[0].velocity().y = 0);
    CHECK(oldt.get_ball()[0].velocity().x = 1);
    CHECK(oldt.get_ball()[0].velocity().y = 0);
    CHECK(t.get_ball()[0].get_bounce_count() = 1);
    CHECK(oldt.get_ball()[0].get_bounce_count() = 1);

    // Check if red gained money
    CHECK(t.get_red().get_money() = 300);
    CHECK(oldt.get_red().get_money() = 300);

    // Check that blue didn't gain money
    CHECK(t.get_blue().get_money() = 200);
    CHECK(oldt.get_blue().get_money() = 200);
}

TEST_CASE("Ball destroyed") {
    // Ball exceeds two-bounce limit and gets destroyed

    Model m;
    Ball b(Player::red, {6, 0}, {-1, 0}, 1); // This version of constructor also takes in lifetime value;
    Test_access t{m};
    t.get_ball().clear();

    // Put the ball in play
    t.get_ball().push_back(b);

    // Use to check if the helper functions work
    Test_access oldt{m};

    // It shouldn't be hitting the wall right now
    CHECK_FALSE(oldt.get_ball()[0].hit_left_wall());

    // Updates the motion of the ball and checks/adjusts if there is any contact
    t.update_balls();

    // Manually update using the helper functions
    oldt.get_ball()[0].move_ball();

    // Check to see if actually registered that it hit the wall
    CHECK(oldt.get_ball()[0].hit_left_wall());

    // Check if red gained money
    CHECK(t.get_red().get_money() = 300);
    CHECK(oldt.get_red().get_money() = 300);

    // Check that blue didn't gain money
    CHECK(t.get_blue().get_money() = 200);
    CHECK(oldt.get_blue().get_money() = 200);

    // Both balls should be destroyed
    CHECK(oldt.get_ball().size() == 0);
    CHECK(t.get_ball().size() == 0);
}

TEST_CASE("Turret fires?") {
    Model m;
    Test_access t{m};

    // Check that when game starts, no balls are active
    CHECK(t.get_ball().size() == 0);

    // Fire a ball
    t.get_turret()[0].fire_ball();

    // Check that there is one ball active in the field currently
    CHECK(t.get_ball().size() == 1);

    // Let's now destroy that ball
    t.get_ball()[0].destroy_ball();

    // Call update once (first call to update will fire ball)
    t.update();

    // Check that there is two balls active in the field currently
    // Both of the default turrets will fire
    CHECK(t.get_ball().size() == 2);

    // Let's now destroy those balls
    t.get_ball().clear();

    // At it's given level, it needs to wait for a certain amount of calls to update
    // (let's say 300) before it fires again. So let's call update 300 times
    for (int i = 0; i < 300; i++) {
        t.update();
    }

    // Check that there is two balls active in the field currently
    // Both of the default turrets will fire
    CHECK(t.get_ball().size() == 2);

    // Let's now destroy those balls
    t.get_ball().clear();
}

TEST_CASE("Ball to top wall") {
    Model m;
    Ball b(Player::red, {10, 6}, {2, -1});
    Test_access t{m};
    t.get_ball().clear();

    // Put the ball in play
    t.get_ball().push_back(b);

    // Use to check if the helper functions work
    Test_access oldt{m};

    // It shouldn't be hitting the wall right now
    CHECK_FALSE(oldt.get_ball()[0].hit_top_wall());

    // Updates the motion of the ball and checks/adjusts if there is any contact
    t.update_balls();

    // Manually update using the helper functions
    oldt.get_ball()[0].move_ball();

    // Check to see if actually registered that it hit the wall
    CHECK(oldt.get_ball()[0].hit_top_wall());

    // Both balls should have a reversed x velocity and red should not gain money
    // Both balls should also have a lifetime of 1
    CHECK(t.get_ball()[0].velocity().x = 2);
    CHECK(t.get_ball()[0].velocity().y = 1);
    CHECK(oldt.get_ball()[0].velocity().x = 2);
    CHECK(oldt.get_ball()[0].velocity().y = 1);
    CHECK(t.get_ball()[0].get_bounce_count() = 1);
    CHECK(oldt.get_ball()[0].get_bounce_count() = 1);

    // Check that red didn't gain money
    CHECK(t.get_red().get_money() = 200);
    CHECK(oldt.get_red().get_money() = 200);

    // Check that blue didn't gain money
    CHECK(t.get_blue().get_money() = 200);
    CHECK(oldt.get_blue().get_money() = 200);
}