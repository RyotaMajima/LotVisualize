#pragma once

#include "define.h"


class Lot{
private:
    static int NUM;
public:
    int pcs;
    int time; //duaration time from starting DB
    string current;
    string next;
    bool nowProcess;

public:
    Lot(); //constructor
    void showData(); //show lot state
};

int Lot::NUM = 0;

Lot::Lot(){
    pcs = 8960;
    time = 0;
    current = "None";
    next = "DB";
    nowProcess = false;
    NUM++;
}

void Lot::showData(){


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
