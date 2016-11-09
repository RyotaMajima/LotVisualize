#include "header.h"

InProcess::InProcess(){
    name = "";
    num = 0;
    pos = Position(0, 0);
}

InProcess::InProcess(string _name, Position _pos){
    name = _name;
    num = 0;
    pos = _pos;
}

InProcess::InProcess(const InProcess &rhs){
    name = rhs.name;
    num = rhs.num;
    pos = rhs.pos;
}