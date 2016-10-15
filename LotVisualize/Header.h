#pragma once

#include "define.h"


class Lot{
private:
    static int NUM;
public:
    int lotNum;
    int pcs;
    int time; //duaration time from starting DB
    string current;
    string next;
    bool nowProcess;

public:
    Lot(); //constructor
    void showData(); //show lot state
    void start(Process prc); //lot starting for some process
};

int Lot::NUM = 0;

Lot::Lot(){
    NUM++;
    lotNum = NUM;
    pcs = 8960;
    current = "Wafer";
    next = "DB";
    nowProcess = false;
}

void Lot::showData(){
    cout << "No." << lotNum << "\t" << pcs << "\t";
    cout << current << "\t" << next << "\t";
    cout << boolalpha << nowProcess << endl;
}

void start(Process prc){

}

class Process{
public:
    string name;
    int processTime;
    bool isUsed;
    int currentLot;
    int time;

public:
    Process(string _name, int _processTime); //constructor
};

Process::Process(string _name, int _processTime){
    name = _name;
    processTime = _processTime;
    isUsed = false;
    currentLot = 0;
    time = 0;
}
