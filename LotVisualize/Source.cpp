#include "Header.h"

int Lot::NUM = 1;

Lot::Lot(){
    lotNum = NUM++;
    qty = (lotNum % 4 != 0) ? 8960 : 1440; //quantity of this lot
    current = "None";
    next = "DB";
    nowProcess = false;
    leadTime = 0;
    Process::inProcess[0].second++; //in-Process of "DB" increment
}

void Lot::showStatus() const{
    cout << "No." << lotNum << "\t" << qty << "\t";
    cout << current << "\t" << next << "\t";
    cout << boolalpha << nowProcess << endl;
}

vector<pair<string, int>> Process::inProcess{
    make_pair("DB", 0), make_pair("DB_CURE", 0),
    make_pair("WB", 0), make_pair("RESIN", 0),
    make_pair("MOLD", 0)
};

Process::Process(string _name, string _nextName, int _machineNo, int _processTime){
    name = _name;
    nextName = _nextName;
    machineNo = _machineNo;
    processTime = _processTime;
    isUsed = false;
    time = 0;
    curtNo = 0;
    cnt = 0;
}

void Process::showStatus() const{
    //int lotNum = index;
    cout << name << "\t" << machineNo << "\t" << nextName << "\t";
    cout << boolalpha << isUsed << "\t";
    if (isUsed){
        cout << curtNo << endl;
    }
    else{
        cout << "empty" << endl;
    }
}

bool Process::hasNext(){
    int idx = getInProcessIndex(name);
    return inProcess[idx].second > 0;
}

int Process::searchLot(vector<Lot> &product){
    auto itr = find_if(product.begin(), product.end(),
        [&](Lot &lot){return lot.nowProcess == false && lot.next == name; });
    if (itr != product.end()){
        return distance(product.begin(), itr);
    }
    else{
        return -1; //lot is not found
    }
}

int Process::getInProcessIndex(string str){
    auto itr = find_if(inProcess.begin(), inProcess.end(),
        [&](pair<string, int> &pair){ return pair.first == str; });
    if (itr != inProcess.end()){
        return distance(inProcess.begin(), itr);
    }
    else{
        cerr << "Process " << str << " is not found" << endl;
        return -1;
    }
}

void Process::lotStart(vector<Lot> &product){
    curtNo = searchLot(product);

    if (curtNo < 0){
        cerr << "next " << name << " lot is not found" << endl;
        return;
    }
    else{
        cout << "No." << product[curtNo].lotNum << " " << name << " start" << endl;
        product[curtNo].current = name;
        product[curtNo].next = nextName;
        product[curtNo].nowProcess = true;
        isUsed = true;
        cnt++;
        int idx = getInProcessIndex(name);
        inProcess.at(idx).second--;
    }
}

void Process::lotEnd(vector<Lot> &product){
    cout << "No." << product[curtNo].lotNum << " " << name << " end" << endl;
    product[curtNo].nowProcess = false;
    isUsed = false;
    time = 0;
    curtNo = 0;
    int idx = getInProcessIndex(nextName);
    inProcess.at(idx).second++;
}

void Process::update(){
    time += timeStep;
}