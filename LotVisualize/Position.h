#pragma once
#include "define.h"

class Position{
private:
    double x, y;
public :
    Position(double _x, double _y);
    void output(ofstream &ofs) const;
    Position& operator=(const Position &rhs);
};