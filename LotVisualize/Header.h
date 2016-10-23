#pragma once

#include "define.h"

class Lot{
private:
    static int NUM; //number of created lot
public:
    int lotNum; //Lot No.
    int pcs;
    int leadTime; //duaration time from starting DB
    string current; //name of current process
    string next; //name of next process
    bool nowProcess;

public:
    Lot(); //constructor
    void showStatus() const; //show lot state
};

class Process{
public:
    static vector<pair<string, int>> inProcess;
public:
    string name; //name of this process
    string nextName; //name of next process
    int machineNo;
    int processTime; //time for lot end
    bool isUsed;
    int time; //time from lot start
    int index; //index for current lot (-1 stands for error)
    int cnt; // count of producted lot

public:
    Process(string _name, string _nextName, int _machineNo, int _processTime); //constructor
    void showStatus() const;
    int searchLot(vector<Lot> &product); //sesrching next lot
    void lotStart(vector<Lot> &product);
    void lotEnd(vector<Lot> &product);
    void update(); //update under processing lot
};