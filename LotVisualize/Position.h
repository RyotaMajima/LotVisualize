#pragma once

class Position{
public:
    double x, y;
public :
    Position();
    Position(double _x, double _y);
    void output(ofstream &ofs, int i) const;
    Position& operator=(const Position& rhs);
};