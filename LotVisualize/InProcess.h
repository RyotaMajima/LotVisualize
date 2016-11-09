#pragma once

class InProcess{
public:
    string name;
    int num;
    Position pos;

public:
    InProcess();
    InProcess(string _name, Position _pos);
    InProcess(const InProcess &rhs);
};