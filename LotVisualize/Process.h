#pragma once

class Process{
public:
    static vector<tuple<string, int, double, double>> inProcess;
    static void outputInProcess(ofstream &ofs);
public:
    string name; //name of this process
    string nextName; //name of next process
    int machineNo;
    int processTime; //time for lot end
    bool isUsed;
    bool isExtra;
    int time; //time from lot start
    int curtNo; //index for current lot (-1 stands for error)
    int cnt; // count of producted lot
    Position pos;

private:
    double pos_x, pos_y;


public:
    Process(string _name, string _nextName, int _machineNo, int _processTime, double _pos_x, double _pos_y); //constructor
    void showStatus() const; //show process status
    bool hasNext(); //return whether is there in-process lot
    int searchLot(vector<Lot> &product); //searching next lot
    void lotStart(vector<Lot> &product);
    void lotEnd(vector<Lot> &product);
    void update(); //update under processing lot
    int getInProcessIndex(string str);
    void output(ofstream &ofs);
};