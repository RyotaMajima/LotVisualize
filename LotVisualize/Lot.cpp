#include "header.h"

int Lot::NUM = 0;

Lot::Lot(){
    lotNum = NUM++;
    isExtra = (lotNum % 4 == 0);
    qty = isExtra ? 1440 : 8960; //quantity of this lot
    tag = Tag("None", "DB");
    nowProcess = false;
    leadTime = 0;
    Process::inProcess[0].dq.push_back(lotNum); //in-Process of "DB" push_back
}

void Lot::showStatus() const{
    cout << "No." << lotNum << "\t" << qty << "\t";
    cout << tag.thisName << "\t" << tag.nextName << "\t";
    cout << boolalpha << nowProcess << endl;
}