#pragma once
#include <array>
namespace cppcraft::world
{
class Position
{
private:
    int16_t x, y, z;
public:
    Position();
    Position(int16_t x, int16_t y, int16_t z);
    int16_t GetX();
    int16_t GetY();
    int16_t GetZ();
    Position SetPosition(int16_t x, int16_t y, int16_t z);
    Position GetPosition();
    std::array<int, 3> ToArray(); // {x, y, z}
    ~Position();
};
}