#pragma once

#include "ge211_audio.h"
#include "ge211_color.h"
#include "ge211_error.h"
#include "ge211_event.h"
#include "ge211_forward.h"
#include "ge211_geometry.h"
#include "ge211_random.h"
#include "ge211_resource.h"
#include "ge211_session.h"
#include "ge211_time.h"

#include <memory>
#include <string>

namespace ge211 {

/** This is the abstract base class for deriving games.
 *
 * To create a new game, you must define a new struct or class that derives
 * from Abstract_game and includes the state for your game, including
 * any model, view (sprites), and controller state. Then you must
 * override various handler functions to specify the behavior of your game.
 * If nothing else, the Abstract_game::draw(Sprite_set&) function must be
 * overridden to specify how to draw your game.
 *
 * For example, here is a game that creates one rectangular sprites::Sprite and
 * renders it on the screen:
 *
 * ```cpp
 * #include <ge211.h>
 *
 * using namespace ge211;
 *
 * struct My_game : Abstract_game
 * {
 *     Rectangle_sprite rect{Dimensions{300, 200}, Color::medium_red()};
 *
 *     void draw(Sprite_set& sprites) override
 *     {
 *         sprites.add_sprite(rect, Position{100, 100});
 *     }
 * };
 *
 * int main()
 * {
 *     My_game{}.run();
 * }
 * ```
 *
 * Note that sprites must be created outside draw(Sprite_set&), because they
 * need to continue to exist after that function returns. Thus, the usual place
 * to define sprites is as member variables of your game struct or class. In
 * more advanced cases, you may store sprites in a view class.
 *
 * Here is a game that creates one circular sprite and renders it wherever
 * the mouse goes:
 *
 * ```cpp
 * #include <ge211.h>
 *
 * using namespace ge211;
 *
 * struct My_game2 : Abstract_game
 * {
 *     // Holds the most recent position of the mouse:
 *     Position last_mouse{0, 0};
 *
 *     // Saves the most recent most position each time the
 *     // mouse moves:
 *     void on_mouse_move(Position mouse) override
 *     {
 *         last_mouse = mouse;
 *     }
 *
 *     // The circle sprite to render where the mouse is:
 *     Circle_sprite cursor{10, Color::medium_blue()};
 *
 *     // Whenever we need to redraw the screen, add the Circle_sprite
 *     // at the mouse position.
 *     void draw(Sprite_set& sprites) override
 *     {
 *         sprites.add_sprite(cursor, last_mouse);
 *     }
 * };
 *
 * int main()
 * {
 *     My_game2{}.run();
 * }
 * ```
 */
class Abstract_game
{
public:

    /// Runs the game. Usually the way to use this is to create an instance of
    /// your game class in `main` and then call run() on it.
    void run();

    /// The default background color of the window, if not changed by the
    /// derived class. To change the background color, assign the protected
    /// member variable Abstract_game::background_color from the
    /// draw(Sprite_set&) or on_start() functions.
    static const Color default_background_color;

    /// The default initial window title. You can change this in a derived class
    /// by overriding the initial_window_title() const member function.
    static const char* const default_window_title;

    /// The default window dimensions, in pixels. You can change this in a
    /// derived class by overriding the initial_window_dimensions() const member
    /// function.
    static const Dimensions default_window_dimensions;

protected:
    /// \name Functions to be overridden by clients
    ///@{

    /// You must override this function in the derived class to specify how
    /// to draw your scene. This function is called by the game engine once
    /// per frame, after handling events. It is passed a Sprite_set; add
    /// sprites to the Sprite_set to have them rendered to the screen.
    ///
    /// Note that the sprites added to the Sprite_set cannot be local
    /// variables owned by the draw(Sprite_set&) function itself, as
    /// they must continue to live after the function returns. For this
    /// reason, they are usually stored as members in the game class, or
    /// in a data structure that is a member of the game class.
    virtual void draw(Sprite_set&) = 0;

    /// Called by the game engine once per frame. The parameter is the duration
    /// of the previous frame in seconds. Override this function to react to time
    /// passing in order to implement animation.
    virtual void on_frame(double last_frame_seconds) {
        (void) last_frame_seconds;
    }

    /// Called by the game engine for each keypress. This uses the system's
    /// repeating behavior, so the user holding down a key can result in multiple
    /// events being delivered. To find out exactly when keys go down and up,
    /// override on_key_down(Key) and on_key_up(Key) instead.
    virtual void on_key(Key) { }

    /// Called by the game engine each time a key is depressed.
    /// Note that this function is delivered the actual key pressed, not the
    /// character that would be generated. For example, if shift is down
    /// and the *5 / %* key is pressed, the delivered key code is `'5'`, not
    /// `'%'`. Similarly, letter keys deliver only lowercase key codes. If
    /// you want key presses interpreted as characters, override on_key(Key)
    /// instead.
    ///
    /// The default behavior of this function, if not overridden, is to quit
    /// if the escape key (code 27) is pressed.
    virtual void on_key_down(Key);

    /// Called by the game engine each time a key is released. This delivers
    /// the same raw key code as on_key_down(Key).
    virtual void on_key_up(Key) { }

    /// Called by the game engine each time a mouse button is depressed.
    virtual void on_mouse_down(Mouse_button, Position) { }

    /// Called by the game engine each time a mouse button is released.
    virtual void on_mouse_up(Mouse_button, Position) { }

    /// Called by the game engine each time the mouse moves.
    virtual void on_mouse_move(Position) { }

    /// Called by the game engine after initializing the game but before
    /// commencing the event loop. You can do this to perform initialization
    /// tasks such as preparing sprites::Sprite%s with
    /// prepare(const Sprite&) const.
    virtual void on_start() { }

    /// Called by the game engine after exiting the event loop but before
    /// the game instance is destroyed. Overriding the function cannot be
    /// used to show anything to the user, since no more rendering will be
    /// performed. It could, however, be used to save a file or shutdown
    /// a network connection.
    ///
    /// Note that this function is called only if the game exits
    /// normally, by calling quit(), or by the user telling
    /// the OS to quit the program. It is not called on exceptions or
    /// errors.
    virtual void on_quit() { }

    /// Override this function to specify the initial dimensions of the
    /// game's window.
    /// This is only called by the engine once at startup.
    virtual Dimensions initial_window_dimensions() const;

    /// Override this function to specify the initial title of the game.
    /// This is only called by the engine once at startup. To change the
    /// title during the game, use get_window() const and
    /// Window::set_title(const std::string&).
    virtual std::string initial_window_title() const;

    ///@}

    /// \name Functions to be called by clients
    ///@{

    /// Causes the event loop to quit after the current frame finishes.
    void quit() noexcept;

    /// Gets the Window that the game is running in. This can be used to query
    /// its size, change its title, etc.
    ///
    /// exceptions::Client_logic_error will be thrown if this function is
    /// called before the window is created by `run()`.
    Window& get_window() const;

    /// Gets the pseudo-random number generator associated with this game.
    /// See the documentation for Random to find out how this can be used to
    /// produce random numbers.
    Random& get_random() const noexcept;

    /// Gets the audio mixer, which can be used to play music. If the
    /// Mixer could not be initialized, this function returns `nullptr`.
    /// Do not delete the result of this function, as it is borrowed from
    /// a private Mixer object stored by this class.
    Mixer* get_mixer() const noexcept;

    /// Gets the time point at which the current frame started. This can be
    /// used to measure intervals between events, though it might be better
    /// to use a time::Timer or time::Pausable_timer.
    Time_point get_frame_start_time() const noexcept
    { return frame_start_.start_time(); }

    /// Returns the duration of the frame right before the frame currently
    /// running. See time::Duration for information on how to use the result.
    Duration get_prev_frame_length() const noexcept
    { return prev_frame_length_; }

    /// Returns an approximation of the current frame rate in Hz.
    /// Typically we synchronize the frame rate with the video controller, but
    /// accessing it might be useful for diagnosing performance problems.
    double get_frame_rate() const noexcept
    { return fps_; }

    /// Prepares a sprites::Sprite for rendering, without actually including it
    /// in the scene. The first time a sprites::Sprite is rendered, it ordinarily
    /// has to be converted and transferred to video memory. This function
    /// performs that conversion and transfer eagerly instead of waiting
    /// for it to happen the first time the sprites::Sprite is used. Careful use of
    /// preparation can be used to control when pauses happen and make other
    /// parts of the game smoother. The easiest thing is often to prepare
    /// all sprites you intend to use from an overridden `on_start()`
    /// function.
    void prepare(const sprites::Sprite&) const;

    ///@}

    /// Assign this member variable to change the window's background color
    /// in subsequent frames. The usual place to assign this variable is from
    /// your overridden on_start() and/or draw(Sprite_set&) functions.
    Color background_color = default_background_color;

private:
    friend detail::Engine;

    void mark_frame_() noexcept;

    mutable Random rng_;
    detail::Session session_;
    std::unique_ptr<audio::Mixer> mixer_ = audio::Mixer::open_mixer();
    detail::Engine* engine_ = nullptr;

    bool quit_ = false;

    Timer frame_start_;
    Duration prev_frame_length_;
    Timer fps_sample_start_;
    int fps_sample_count_{0};
    double fps_{0};
};

}
