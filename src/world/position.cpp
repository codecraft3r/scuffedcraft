#include "world/position.h"
#include <iostream>

namespace cppcraft::world
{

Position::Position() : x(-INT16_MAX), y(-INT16_MAX), z(-INT16_MAX) {}
Position::Position(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}

Position Position::SetPosition(int16_t x, int16_t y, int16_t z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

Position Position::GetPosition()
{
    if (x == -INT16_MAX || y == -INT16_MAX || z == -INT16_MAX)
    {
        std::cerr << "Position not set before calling GetPosition! Returned position has -INT16_MAX values, you probably don't want this." << std::endl;
    }
    return *this;
}

std::array<int, 3> Position::ToArray()
{
    if (x == -INT16_MAX || y == -INT16_MAX || z == -INT16_MAX)
    {
        std::cerr << "Position not set before calling ToArray! Returned position has -INT16_MAX values, you probably don't want this." << std::endl;
    }
    return {x, y, z};
}

int16_t Position::GetX()
{
    if (x == -INT16_MAX)
    {
        std::cerr << "Position not set before calling GetX, returning -INT16_MAX" << std::endl;
    }
    return x;
}

int16_t Position::GetY()
{
    if (y == -INT16_MAX)
    {
        std::cerr << "Position not set before calling GetY, returning -INT16_MAX" << std::endl;
    }
    return y;
}

int16_t Position::GetZ()
{
    if (z == -INT16_MAX)
    {
        std::cerr << "Position not set before calling GetZ, returning -INT16_MAX" << std::endl;
    }
    return z;
}
Position::~Position() {}

}