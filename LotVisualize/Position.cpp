#include "header.h"

Position::Position() = default;

Position::Position(double _x, double _y)
    :x(_x), y(_y){}

void Position::output(ofstream &ofs) const{
    ofs << x << "\t" << y;
}

Position& Position::operator=(const Position& rhs){
    x = rhs.x;
    y = rhs.y;
    return *this;
}