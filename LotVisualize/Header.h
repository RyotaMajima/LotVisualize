#pragma once

#include "define.h"

enum{
    _None, _Wafer,_DB,_WB
};

class Lot{
public:
    int pcs;
    int time;
    int current;
    int next;
    bool nowProcess;

public:
    Lot(); //constructor
};

Lot::Lot(){
    pcs = 8960;
    time = 0;
    current = _Wafer;
    next = _DB;
    nowProcess = false;
}

class Process{
public:
    int capacity;
    double processTime;
    bool isEmpty;

public:
    Process(); //constructor
};

Process::Process(){
    capacity = 1;
    processTime = 15;
    isEmpty = true;
}
