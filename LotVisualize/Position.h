#pragma once
#include "define.h"

class Position{
private:
    double x, y;
public :
    Position();
    void output(ofstream &ofs) const;
    Position& operator=(Position &rhs) const;
};