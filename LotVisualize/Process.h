#pragma once

class Process{
public:
    static vector<tuple<string, int, double, double>> inProcess;
    static void outputInProcess(ofstream &ofs);

public:
    Tag tag;
    int machineNo;
    int capacity;
    int processTime; //time for lot end
    bool isUsed;
    bool isExtra;
    int time; //time from lot start
    //int curtNo; //index for current lot (-1 stands for error)
    vector<int> curtNo;
    int cnt; // count of producted lot
    Position pos;

public:
    Process(Tag _tag, int _machineNo, int _processTime, int _capacity);
    void showStatus() const; //show process status
    bool hasInProcess(); //return whether are there proper in-process lots
    int searchLot(vector<Lot> &product); //searching next lot
    int getInProcessIndex(string str);
    void lotStart(vector<Lot> &product);
    void lotEnd(vector<Lot> &product);
    void update(); //update under processing lot
    void setPos(const Position &other);
    void fileOutput(ofstream &ofs);
    void writePos(vector<Lot> &product);
};