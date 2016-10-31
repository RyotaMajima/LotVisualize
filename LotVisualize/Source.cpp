#include "Header.h"

int Lot::NUM = 1;

Lot::Lot(){
    lotNum = NUM++;
    extra = (lotNum % 4 == 0);
    qty = extra ? 1440 : 8960; //quantity of this lot
    current = "None";
    next = "DB";
    nowProcess = false;
    leadTime = 0;
    get<1>(Process::inProcess[0])++; //in-Process of "DB" increment
}

void Lot::showStatus() const{
    cout << "No." << lotNum << "\t" << qty << "\t";
    cout << current << "\t" << next << "\t";
    cout << boolalpha << nowProcess << endl;
}

vector<tuple<string, int, double, double>> Process::inProcess{
    make_tuple("DB", 0, -19, 18), make_tuple("DB_CURE", 0, 11, 15),
    make_tuple("WB", 0, 5, 0), make_tuple("RESIN", 0, -15, 1),
    make_tuple("RESIN_CURE", 0, -10, -10), make_tuple("PLASMA", 0, -10, 0)
};

void Process::outputInProcess(ofstream &ofs){
    for (auto &prc : inProcess){
        for (int i = 0; i < get<1>(prc); i++){
            ofs << get<2>(prc) + (i * 2) << "\t" << get<3>(prc) << endl;
        }
        ofs << endl;
    }
}

Process::Process(string _name, string _nextName, int _machineNo, int _processTime, double _pos_x, double _pos_y){
    name = _name;
    nextName = _nextName;
    machineNo = _machineNo;
    processTime = _processTime;
    pos_x = _pos_x;
    pos_y = _pos_y;
    isUsed = false;
    time = 0;
    curtNo = 0;
    cnt = 0;
}

void Process::showStatus() const{
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
    return get<1>(inProcess[idx]) > 0;
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
        [=](tuple<string, int, double, double> &tuple){ return get<0>(tuple) == str; });
    if (itr != inProcess.end()){
        return distance(inProcess.begin(), itr);
    }
    else{
        cerr << "Process " << str << " is not found" << endl;
        return -1; //process is not found
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
        time = 0;
        cnt++;
        int idx = getInProcessIndex(name);
        get<1>(inProcess[idx])--;
    }
}

void Process::lotEnd(vector<Lot> &product){
    cout << "No." << product[curtNo].lotNum << " " << name << " end" << endl;
    product[curtNo].nowProcess = false;
    isUsed = false;
    time = 0;
    curtNo = 0;
    int idx = getInProcessIndex(nextName);
    get<1>(inProcess[idx])++;
}

void Process::update(){
    time += timeStep;
}

void Process::output(ofstream &ofs){
    if (isUsed){
        ofs << pos_x << "\t" << pos_y << endl;
    }
}