#include "ge211_geometry.h"

#include <cmath>

namespace ge211 {

namespace geometry {

Transform::Transform() noexcept
        : rotation_{0}, scale_x_{1.0}, scale_y_{1.0},
          flip_h_{false}, flip_v_{false}
{ }

Transform Transform::rotation(double degrees) noexcept
{
    return Transform().set_rotation(degrees);
}

Transform Transform::flip_h() noexcept
{
    return Transform().set_flip_h(true);
}

Transform Transform::flip_v() noexcept
{
    return Transform().set_flip_v(true);
}

Transform Transform::scale(double factor) noexcept
{
    return Transform().set_scale(factor);
}

Transform Transform::scale_x(double factor) noexcept
{
    return Transform().set_scale_x(factor);
}

Transform Transform::scale_y(double factor) noexcept
{
    return Transform().set_scale_y(factor);
}

Transform& Transform::set_rotation(double rotation) noexcept
{
    while (rotation < 0) rotation += 360;
    rotation_ = std::fmod(rotation, 360);
    return *this;
}

Transform& Transform::set_flip_h(bool flip_h) noexcept
{
    flip_h_ = flip_h;
    return *this;
}

Transform& Transform::set_flip_v(bool flip_v) noexcept
{
    flip_v_ = flip_v;
    return *this;
}

Transform& Transform::set_scale(double scale) noexcept
{
    scale_x_ = scale;
    scale_y_ = scale;
    return *this;
}

Transform& Transform::set_scale_x(double scale_x) noexcept
{
    scale_x_ = scale_x;
    return *this;
}

Transform& Transform::set_scale_y(double scale_y) noexcept
{
    scale_y_ = scale_y;
    return *this;
}

double Transform::get_rotation() const noexcept
{
    return rotation_;
}

bool Transform::get_flip_h() const noexcept
{
    return flip_h_;
}

bool Transform::get_flip_v() const noexcept
{
    return flip_v_;
}

double Transform::get_scale_x() const noexcept
{
    return scale_x_;
}

double Transform::get_scale_y() const noexcept
{
    return scale_y_;
}

bool Transform::is_identity() const noexcept
{
    return *this == Transform();
}

Transform Transform::operator*(const Transform& other) const noexcept
{
    Transform result;
    result.set_rotation(rotation_ + other.rotation_);
    result.set_flip_h(flip_h_ ^ other.flip_h_);
    result.set_flip_v(flip_v_ ^ other.flip_v_);
    result.set_scale_x(scale_x_ * other.scale_x_);
    result.set_scale_y(scale_y_ * other.scale_y_);
    return result;
}

Transform Transform::inverse() const noexcept
{
    Transform result;
    result.set_rotation(-rotation_);
    result.set_flip_h(flip_h_);
    result.set_flip_v(flip_v_);
    result.set_scale_x(1 / scale_x_);
    result.set_scale_y(1 / scale_y_);
    return result;
}

bool operator==(const Transform& t1, const Transform& t2) noexcept
{
    return t1.get_rotation() == t2.get_rotation() &&
            t1.get_flip_h() == t2.get_flip_h() &&
            t1.get_flip_v() == t2.get_flip_v() &&
            t1.get_scale_x() == t2.get_scale_x() &&
            t1.get_scale_y() == t2.get_scale_y();
}

bool operator!=(const Transform& t1, const Transform& t2) noexcept
{
    return !(t1 == t2);
}

}

}
