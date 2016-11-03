#pragma once
#include "header.h"

class InProcess{
private:
    int num;
    Position pos;

public:
    InProcess();
    void increase();
    void decrease();
    bool exist();

};