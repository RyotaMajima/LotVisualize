#pragma once
#include "InProcess.h"

enum struct State{
    WORK, CHG, CHGED, TRB, WAIT
};

class Process{
public:
    static vector<InProcess> inProcess;
    static void outputInProcess(ofstream &ofs, vector<Lot> &product);

public:
    Tag name;
    int machineNo;
    int capacity;
    int processTime; //time for lot end
    //bool isUsed;
    vector<bool> isExtra;
    int time; //time from lot start
    vector<int> curtNo; //index for current lot (-1 stands for error)
    int cnt; // count of producted lot
    State state;
    Position pos;

public:
    Process(Tag _name, int _machineNo, int _processTime, int _capacity);
    void showStatus() const; //show process status
    bool hasInProcess(); //return whether are there proper in-process lots
    int getInProcessIndex(string str);
    void lotChange();
    void lotStart(vector<Lot> &product);
    void lotEnd(vector<Lot> &product);
    void update(vector<Lot> &product); //update under processing lot
    void fileOutput(ofstream &ofs);
};