#pragma once

#include "define.h"

enum{
    Wafer,DB,WB
};

class Lot{
public:
    int pcs;

public:
    Lot(); //constructor
};

Lot::Lot(){
    pcs = 8960;
}

class State{
public:
    int nextProcess;
    int currentProcess;
public:
    State();
};

State::State(){
    currentProcess = Wafer;
    nextProcess = DB;
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
    processTime = 25;
    isEmpty = true;
}
