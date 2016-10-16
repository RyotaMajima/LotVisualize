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

//void start(Process prc){
//
//}

class Process{
public:
    string name;
    string nextName;
    int processTime;
    bool isUsed;
    int currentLot;
    int time;
    int index;
    int cnt;

public:
    Process(string _name, string nextName, int _processTime); //constructor
    int searchLot(vector<Lot> &product);
    void lotStart(vector<Lot> &product);
    void lotEnd(vector<Lot> &product);
    void update();
};

Process::Process(string _name, string _nextName, int _processTime){
    name = _name;
    nextName = _nextName;
    processTime = _processTime;
    isUsed = false;
    currentLot = 0;
    time = 0;
    index = -1;
    cnt = 0;
}

int Process::searchLot(vector<Lot> &product){
    for (int i = 0; i < N; i++){
        if (product[i].next == name){
            return i;
        }
    }

    return -1;
}

void Process::lotStart(vector<Lot> &product){
    index = searchLot(product);

    if (index < 0){
        cerr << "next " << name << " lot is not found" << endl;
        return;
    }
    else{
        cout << "No." << product[index].lotNum << " " << name << "  start" << endl;
        product[index].current = name;
        product[index].nowProcess = true;
        isUsed = true;
        cnt++;
    }
}

void Process::lotEnd(vector<Lot> &product){
    product[index].current = "None";
    product[index].next = nextName;
    product[index].nowProcess = false;
    isUsed = false;
    index = -1;
}

void Process::update(){
    time += timeStep;
}