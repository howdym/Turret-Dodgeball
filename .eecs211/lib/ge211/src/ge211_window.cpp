#include "ge211_window.h"
#include "ge211_error.h"

#include <SDL.h>

namespace ge211 {

using namespace detail;

Window::Window(const std::string& title, Dimensions dim)
        : ptr_{SDL_CreateWindow(title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                dim.width,
                                dim.height,
                                SDL_WINDOW_SHOWN),
               &SDL_DestroyWindow}
{
    if (ptr_ == nullptr)
        throw Host_error{"Could not create window"};
}

uint32_t Window::get_flags_() const noexcept
{
    return SDL_GetWindowFlags(get_raw_());
}

Dimensions Window::get_dimensions() const noexcept
{
    Dimensions result{0, 0};
    SDL_GetWindowSize(get_raw_(), &result.width, &result.height);
    return result;
}

void Window::set_dimensions(Dimensions dims)
{
    SDL_SetWindowSize(get_raw_(), dims.width, dims.height);

    if (get_dimensions() != dims)
        throw Environment_error{"Window::set_dimensions: out of range"};
}

const char* Window::get_title() const noexcept
{
    return SDL_GetWindowTitle(get_raw_());
}

void Window::set_title(const std::string& title) noexcept
{
    SDL_SetWindowTitle(get_raw_(), title.c_str());
}

bool Window::get_resizeable() const noexcept
{
    return (get_flags_() & SDL_WINDOW_RESIZABLE) != 0;
}

void Window::set_resizeable(bool resizable) noexcept
{
    SDL_SetWindowResizable(get_raw_(), resizable? SDL_TRUE : SDL_FALSE);
}

Position Window::get_position() const noexcept
{
    Position result{0, 0};
    SDL_GetWindowPosition(get_raw_(), &result.x, &result.y);
    return result;
}

void Window::set_position(Position position)
{
    SDL_SetWindowPosition(get_raw_(), position.x, position.y);
}

const Position Window::centered{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};

bool Window::get_fullscreen() const noexcept
{
    return (get_flags_() & SDL_WINDOW_FULLSCREEN) != 0;
}

void Window::set_fullscreen(bool fullscreen)
{
    uint32_t flags = fullscreen? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_SetWindowFullscreen(get_raw_(), flags) < 0)
        throw Host_error{"Window::set_fullscreen: failed"};
}

Dimensions Window::max_fullscreen_dimensions() noexcept
{
    SDL_Rect rect;
    SDL_GetDisplayBounds(0, &rect);
    return {rect.w, rect.h};
}

Dimensions Window::max_window_dimensions() const noexcept
{
    int top, left, bottom, right;
    SDL_GetWindowBordersSize(get_raw_(), &top, &left, &bottom, &right);

    SDL_Rect rect;
    SDL_GetDisplayUsableBounds(0, &rect);

    return {rect.w - left - right, rect.h - top - bottom};
}

}
