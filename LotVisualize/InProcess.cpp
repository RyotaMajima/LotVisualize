#include "header.h"

InProcess::InProcess(){
    name = "";
    pos = Position(0, 0);
}

InProcess::InProcess(string _name, Position _pos, int _capacity){
    name = _name;
    //dq.resize(_capacity);
    pos = _pos;
}

InProcess::InProcess(const InProcess &rhs){
    name = rhs.name;
    pos = rhs.pos;
}