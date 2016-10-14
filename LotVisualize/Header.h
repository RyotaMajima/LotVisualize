#pragma once

#include "define.h"

enum{
    _Wafer,_DB,_WB
};

class Lot{
public:
    int pcs;
    int time;
    bool nowProcess;

public:
    Lot(); //constructor
};

Lot::Lot(){
    pcs = 8960;
    time = 0;
    nowProcess = false;
}

class State{
public:
    int nextProcess;
    int currentProcess;
public:
    State();
};

State::State(){
    currentProcess = _Wafer;
    nextProcess = _DB;
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
