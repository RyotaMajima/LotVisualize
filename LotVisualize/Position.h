#pragma once

class Position{
private:
    double x, y;
public :
    Position();
    Position(double _x, double _y);
    void setPos(const Position &pos);
    void output(ofstream &ofs) const;

    Position& operator=(const Position& rhs);
};