#pragma once

#include "ge211_forward.h"
#include "ge211_geometry.h"
#include "ge211_util.h"

#include <string>

namespace ge211 {

/// Provides access to the game window and its properties.
class Window
{
public:
    /// Returns the current dimensions of this window.
    Dimensions get_dimensions() const noexcept;
    /// Changes the size of the window. Throws exceptions::Environment_error
    /// if the dimensions are negative or outside the allowable range.
    void set_dimensions(Dimensions);

    /// Gets the position of the upper-left corner of the window with
    /// respect to the upper-left corner of the screen.
    Position get_position() const noexcept;
    /// Sets the position of the upper-left corner of the window with
    /// respect to the upper-left corner of the screen.
    void set_position(Position);
    /// A special value to pass to set_position(Position) to center
    /// the window on the screen.
    static const Position centered;

    /// Returns the current title of this window.
    ///
    /// The returned pointer should not be freed by the client. It is
    /// borrowed from a buffer stored within the window, and should be
    /// valid until the next call to set_title(const std::string&).
    /// Copy it to a std::string if you need to hold it longer.
    const char* get_title() const noexcept;
    /// Changes the title of this window.
    void set_title(const std::string&) noexcept;

    /// Returns whether the user can resize this window.
    bool get_resizeable() const noexcept;
    /// Changes whether the user can resize this window.
    void set_resizeable(bool) noexcept;

    /// Returns whether the program is in fullscreen mode.
    bool get_fullscreen() const noexcept;
    /// Sets whether the program should be in fullscreen mode. Throws
    /// exceptions::Host_error if change fails.
    void set_fullscreen(bool);

    /// Returns the maximum dimensions for a non-fullscreen window.
    /// This is the size of the screen, minus space reserved for the
    /// system (such as the Windows taskbar or Mac menu and dock).
    Dimensions max_window_dimensions() const noexcept;

    /// Returns the maximum dimensions for a fullscreen window. Call
    /// this before switching to fullscreen mode, since if you fullscreen
    /// a smaller window, the video mode may change.
    static Dimensions max_fullscreen_dimensions() noexcept;

private:
    friend detail::Engine;
    friend detail::Renderer;

    Window(const std::string&, Dimensions dim);

    SDL_Window* get_raw_() const noexcept { return ptr_.get(); }
    uint32_t get_flags_() const noexcept;

    detail::delete_ptr<SDL_Window> ptr_;
};

}
