#pragma once

class Position{
public:
    double x, y;
public :
    Position();
    Position(double _x, double _y);
    Position& operator=(const Position& rhs);
};