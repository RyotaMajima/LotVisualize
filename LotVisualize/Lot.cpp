#include "header.h"

int Lot::NUM = 1;

Lot::Lot(){
    lotNum = NUM++;
    extra = (lotNum % 4 == 0);
    qty = extra ? 1440 : 8960; //quantity of this lot
    tag = Tag("None", "DB");
    nowProcess = false;
    leadTime = 0;
    get<1>(Process::inProcess[0])++; //in-Process of "DB" increment
}

void Lot::showStatus() const{
    cout << "No." << lotNum << "\t" << qty << "\t";
    cout << tag.getThisName() << "\t" << tag.getNextName() << "\t";
    cout << boolalpha << nowProcess << endl;
}

void Lot::fileOutput(ofstream &ofs){
    pos.output(ofs);
    ofs << "\t" << (extra ? 1 : 0) << endl;
}