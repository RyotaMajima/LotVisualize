#pragma once

class InProcess{
public:
    string name;
    deque<int> dq;
    Position pos;

public:
    InProcess();
    InProcess(string _name, Position _pos, int _capacity);
    InProcess(const InProcess &rhs);
};