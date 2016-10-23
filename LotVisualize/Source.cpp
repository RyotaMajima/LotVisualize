#include "Header.h"

int Lot::NUM = 0;

Lot::Lot(){
    lotNum = ++NUM; //change from 0-index to 1-index for products
    pcs = (lotNum % 4 != 0) ? 8960 : 1440;
    leadTime = 0;
    current = "None";
    next = "DB";
    nowProcess = false;
    Process::inProcess[0].second++;
}

void Lot::showStatus() const{
    cout << "No." << lotNum << "\t" << pcs << "\t";
    cout << current << "\t" << next << "\t";
    cout << boolalpha << nowProcess << endl;
}

vector<pair<string, int>> Process::inProcess{
    make_pair("DB", 0), make_pair("DB_CURE", 0),
    make_pair("WB", 0)
};

Process::Process(string _name, string _nextName, int _machineNo, int _processTime){
    name = _name;
    nextName = _nextName;
    machineNo = _machineNo;
    processTime = _processTime;
    isUsed = false;
    time = 0;
    index = -1;
    cnt = 0;
}

void Process::showStatus() const{
    int lotNum = index;
    cout << name << "\t" << machineNo << "\t" << nextName << "\t";
    cout << boolalpha << isUsed << "\t";
    if (lotNum < 0){
        cout << "empty" << endl;
    }
    else{
        cout << ++lotNum << endl;
    }
}

int Process::searchLot(vector<Lot> &product){
    for (int idx = 0; idx < N; idx++){
        if (product[idx].nowProcess == false && product[idx].next == name){
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
        cout << "No." << product[index].lotNum << " " << name << " start" << endl;
        product[index].current = name;
        product[index].next = nextName;
        product[index].nowProcess = true;
        isUsed = true;
        cnt++;
        auto itr = find_if(inProcess.begin(), inProcess.end(),
            [&](pair<string, int> &pair){ return pair.first == name; });
        if (itr != inProcess.end()){
            int dist = distance(inProcess.begin(), itr);
            inProcess[dist].second--;
        }
    }
}

void Process::lotEnd(vector<Lot> &product){
    cout << "No." << product[index].lotNum << " " << name << " end" << endl;
    product[index].nowProcess = false;
    isUsed = false;
    time = 0;
    index = -1;
}

void Process::update(){
    time += timeStep;
}