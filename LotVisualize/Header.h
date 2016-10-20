#pragma once

#include "define.h"

class Lot{
private:
    static int NUM; //number of created lot
public:
    int lotNum; //Lot No.
    int pcs;
    int time; //duaration time from starting DB
    string current; //name of current process
    string next; //name of next process
    bool nowProcess;

public:
    Lot(); //constructor
    void showStatus(); //show lot state
};

int Lot::NUM = 0;

Lot::Lot(){
    lotNum = ++NUM; //change from 0-index to 1-index for products
    pcs = (lotNum % 4 != 0) ? 8960 : 1440;
    time = 0;
    current = "Wafer";
    next = "DB";
    nowProcess = false;
}

//show lot state
void Lot::showStatus(){
    cout << "No." << lotNum << "\t" << pcs << "\t";
    cout << current << "\t" << next << "\t";
    cout << boolalpha << nowProcess << endl;
}

class Process{
public:
    string name; //name of this process
    string nextName; //name of next process
    int processTime; //time for lot end
    bool isUsed;
    int time; //time from lot start
    int index; //index for current lot (-1 stands for error)
    int cnt; // count of producted lot

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
    time = 0;
    index = -1;
    cnt = 0;
}

int Process::searchLot(vector<Lot> &product){
    for (int idx = 0; idx < N; idx++){
        if (product[idx].next == name){
            return idx;
        }
    }

    return -1; //lot is not found
}

void Process::lotStart(vector<Lot> &product){
    index = searchLot(product);

    if (index < 0){
        cerr << "next " << name << " lot is not found" << endl;
        return;
    }
    else{
        cout << endl;
        cout << "No." << product[index].lotNum << " " << name << " start." << endl;
        product[index].current = name;
        product[index].next = nextName;
        product[index].nowProcess = true;
        isUsed = true;
        cnt++;
    }
}

void Process::lotEnd(vector<Lot> &product){
    cout << endl;
    cout << "No." << product[index].lotNum << " " << name << " end." << endl;
    product[index].current = "None";
    product[index].nowProcess = false;
    isUsed = false;
    time = 0;
    index = -1;
}

void Process::update(){
    time += timeStep;
}