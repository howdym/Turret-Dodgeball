#pragma once

// Forward declarations for some useful SDL2 types.
struct SDL_KeyboardEvent;
union SDL_Event;
struct SDL_Renderer;
struct SDL_RWops;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Window;
struct Mix_Chunk;
struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;
struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

// Forward declarations for all ge211 types.
namespace ge211 {

class Abstract_game;
class Color;
class Font;
class Sprite_set;
class Window;

/// Internal implementation details.
namespace detail {

class Engine;
class File_resource;
struct Placed_sprite;
class Renderer;
class Session;
class Render_sprite;
class Texture;
class Texture_sprite;

} // end namespace detail

namespace audio {

enum class Channel_state;
class Mixer;
class Music_track;
class Sound_effect;
class Sound_effect_handle;

} // end namespace audio

namespace events {

class Key;
enum class Mouse_button;

} // end namespace events

namespace exceptions {

class Exception_base;
class Client_logic_error;
class Environment_error;
class Ge211_logic_error;
class Host_error;
class File_error;
class Font_error;
class Image_error;
class Mixer_error;

} // end namespace exception

namespace geometry {

template <class> struct Basic_dimensions;
template <class> struct Basic_position;
template <class> struct Basic_rectangle;

using Dimensions = Basic_dimensions<int>;
using Position = Basic_position<int>;
using Rectangle = Basic_rectangle<int>;
class Transform;

} // end namespace geometry

namespace sprites {

class Sprite;

class Circle_sprite;
class Image_sprite;
class Multiplexed_sprite;
class Rectangle_sprite;
class Text_sprite;

} // end namespace sprites

namespace time {

class Duration;
class Time_point;

class Timer;
class Pausable_timer;

} // end namespace time

// Bring everything but detail into the ge211 namespace.

using namespace audio;
using namespace events;
using namespace exceptions;
using namespace geometry;
using namespace sprites;
using namespace time;

}
