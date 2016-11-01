#include "header.h"

Position::Position(double _x = 0.0, double _y = 0.0)
    :x(_x), y(_y){}

void Position::output(ofstream &ofs) const{
    ofs << x << "\t" << y << endl;
}

Position& Position::operator=(const Position& rhs){
    x = rhs.x;
    y = rhs.y;
}