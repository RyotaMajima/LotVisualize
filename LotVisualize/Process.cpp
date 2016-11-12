#include "header.h"

vector<InProcess> Process::inProcess{
    InProcess{ "DB", { -23, 21 } }, InProcess{ "DB_CURE", {-17, 5} },
    InProcess{ "WB", { -8, 5 } }, InProcess{ "RESIN", {-15, 5} },
    InProcess{ "R_CURE", { 11, 5 } }, InProcess{ "PLASMA", {5, -3} },
    InProcess{ "MOLD", {5, -10} }
};

void Process::outputInProcess(ofstream &ofs){
    for (auto &prc : inProcess){
        for (int i = 0; i < prc.num; i++){
            ofs << prc.pos.x + (i * 1.2) << "\t" << prc.pos.y << endl;
        }
        ofs << endl;
    }
}

Process::Process(Tag _name, int _machineNo, int _processTime, int _capacity){
    name = _name;
    machineNo = _machineNo;
    capacity = _capacity;
    processTime = _processTime;
    isUsed = false;
    isExtra = false;
    time = 0;
    curtNo.resize(capacity);
    cnt = 0;
}

void Process::showStatus() const{
    cout << name.thisName << "\t" << machineNo << "\t" << name.nextName << "\t" << capacity << "\t";
    cout << boolalpha << isUsed << "\t";
    if (isUsed){
        for (auto &val : curtNo){
            cout << val << " ";
        }
        cout << endl;
    }
    else{
        cout << "empty" << endl;
    }
}

bool Process::hasInProcess(){
    int idx = getInProcessIndex(name.thisName);
    return inProcess[idx].num >= capacity;
}

int Process::searchLot(vector<Lot> &product){
    auto itr = find_if(product.begin(), product.end(),
        [&](Lot &lot){return lot.nowProcess == false && lot.tag.nextName == name.thisName; });
    if (itr != product.end()){
        return distance(product.begin(), itr);
    }
    else{
        return -1; //lot is not found
    }
}

int Process::getInProcessIndex(string str){
    auto itr = find_if(inProcess.begin(), inProcess.end(),
        [=](InProcess &prc){ return prc.name == str; });
    if (itr != inProcess.end()){
        return distance(inProcess.begin(), itr);
    }
    else{
        cerr << "Process " << str << " is not found" << endl;
        return -1; //process is not found
    }
}

void Process::lotStart(vector<Lot> &product){
    for (int i = 0; i < capacity; i++){
        curtNo[i] = searchLot(product);

        if (curtNo[i] < 0){
            cerr << "next " << name.thisName << " lot is not found" << endl;
            return;
        }
        else{
            cout << "No." << product[curtNo[i]].lotNum << " " << name.thisName << " start" << endl;
            product[curtNo[i]].tag = name;
            product[curtNo[i]].nowProcess = true;
            isUsed = true;
            isExtra = product[curtNo[i]].isExtra;
            time = 0;
            cnt++;
            int idx = getInProcessIndex(name.thisName);
            (inProcess[idx].num)--;
        }
    }
}

void Process::lotEnd(vector<Lot> &product){
    for (int i = 0; i < capacity; i++){
        cout << "No." << product[curtNo[i]].lotNum << " " << name.thisName << " end" << endl;
        product[curtNo[i]].nowProcess = false;
        isUsed = false;
        time = 0;
        curtNo[i] = 0;
        int idx = getInProcessIndex(name.nextName);
        (inProcess[idx].num)++;
    }
}

void Process::update(){
    time += timeStep;
}

void Process::fileOutput(ofstream &ofs){
    if (isUsed){
        for (int i = 0; i < capacity; i++){
            ofs << pos.x + (i * 1.2) << "\t" << pos.y << "\t";
            ofs << (isExtra ? 1 : 0) << endl;
        }
    }
}