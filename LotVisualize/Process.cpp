#include "header.h"

vector<InProcess> Process::inProcess{
    InProcess{ "DB", { -23, 21 }, 20 }, InProcess{ "DB_CURE", { -17, 5 }, 10 },
    InProcess{ "WB", { -8, 5 }, 5 }, InProcess{ "RESIN", { -2, 5 }, 20 },
    InProcess{ "R_CURE", { 11, 5 }, 4 }, InProcess{ "PLASMA", { 5, -3 }, 30 },
    InProcess{ "MOLD", { 5, -10 }, 3 }, InProcess{ "MARK", { 15, -19 }, 8 },
    InProcess{ "DICING", { 0, -19 }, 10 }, InProcess{ "DIC_CURE", { -15, -19 }, 3 },
    InProcess{ "TPG", { -15, -3 }, 40 }, InProcess{ "REEL", { 35, 0 }, 100 }
};

void Process::outputInProcess(ofstream &ofs, vector<Lot> &product){
    for (auto &prc : inProcess){
        if (!prc.dq.empty()){
            for (size_t i = 0; i < prc.dq.size(); i++){
                ofs << prc.pos.x + ((i % 10) * 1.2) << "\t" << prc.pos.y - (i / 10) * 2.0 << "\t";
                ofs << (product[prc.dq[i]].isExtra ? 1 : 0) << endl;;
            }
            ofs << endl;
        }
    }
}

Process::Process(Tag _name, int _machineNo, int _processTime, int _capacity){
    name = _name;
    machineNo = _machineNo;
    capacity = _capacity;
    processTime = _processTime;
    isExtra.resize(capacity, false);
    time = 0;
    curtNo.resize(capacity, 0);
    cnt = 0;
    state = State::WAIT;
}

void Process::showStatus() const{
    cout << name.thisName << "\t" << machineNo << "\t" << name.nextName << "\t" << capacity << "\t";
    cout << boolalpha << (state == State::WORK) << "\t";
    if (state == State::WORK){
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
    return (int)inProcess[idx].dq.size() >= capacity;
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

void Process::lotChange(){
    int idx = getInProcessIndex(name.thisName);
    if ((int)inProcess[idx].dq.size() < capacity){
        cerr << "dq.size() error in lotChange() ";
        cerr << "in " << name.thisName << " #" << machineNo << endl;
        return;
    }
    for (int i = 0; i < capacity; i++){
        curtNo[i] = inProcess[idx].dq.front();
        inProcess[idx].dq.pop_front();
    }
    state = State::CHGED;
}

void Process::lotStart(vector<Lot> &product){
    int idx = getInProcessIndex(name.thisName);
    for (int i = 0; i < capacity; i++){
        cout << "No." << product[curtNo[i]].lotNum << " " << name.thisName << " start" << endl;
        product[curtNo[i]].tag = name;
        product[curtNo[i]].nowProcess = true;
        state = State::WORK;
        isExtra[i] = product[curtNo[i]].isExtra;

        if (name.thisName.find("CURE") == -1){
            time = isExtra[i] ? processTime / 2 : 0;
        }
        else{
            time = 0;
        }

        cnt++;
    }
}

void Process::lotEnd(vector<Lot> &product){
    for (int i = 0; i < capacity; i++){
        cout << "No." << product[curtNo[i]].lotNum << " " << name.thisName << " end" << endl;
        product[curtNo[i]].nowProcess = false;
        state = State::WAIT;
        time = 0;
        int idx = getInProcessIndex(name.nextName);
        inProcess[idx].dq.push_back(curtNo[i]);
    }
}

void Process::update(vector<Lot> &product){
    switch (state)
    {
    case State::WORK:
        time += timeStep;
        if (time >= processTime){
            lotEnd(product);
        }
        break;
    case State::CHG:
        lotChange();
        break;
    case State::CHGED:
        lotStart(product);
        break;
    case State::TRB:
        break;
    case State::WAIT:
        if (hasInProcess()){
            state = State::CHG;
        }
        break;
    }
}

void Process::fileOutput(ofstream &ofs){
    if (state == State::WORK){
        for (int i = 0; i < capacity; i++){
            ofs << pos.x + (i * 1.2) << "\t" << pos.y << "\t";
            ofs << (isExtra[i] ? 1 : 0) << "\t";
            ofs << static_cast<int>(state) << endl;
        }
    }
}