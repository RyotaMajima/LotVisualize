#include "define.h"
#include "header.h"

const vector<Position> ProcessPos{
    { 1.0, 16.0 }, { 1.0, 13.0 },
    { 16.0, 12.0 }, { 16.0, 9.0 },
    { 1.0, 9.0 }, { 1.0, 6.0 },
    { 1.0, 1.0 }, { 4.0, 1.0 }, { 1.0, -3.0 }, { 4.0, -3.0 },
    { 10.0, -8.0 }
};

const vector<Position> InProcessPos{
    { -19, 18 }, { 11, 15 }, { -15, 10 }, {-15, 1},
    { 10, -2 }, {-10, 0}
};

int main(){
    vector<Process> line{
        //{ tag, MachineNo, processTime, capacity }
        { Tag("DB", "DB_CURE"), 1, 10, 1 },
        { Tag("DB", "DB_CURE"), 2, 10, 1 },
        { Tag("DB_CURE", "WB"), 1, 15, 3 },
        { Tag("DB_CURE", "WB"), 2, 15, 3 },
        { Tag("WB", "RESIN"), 1, 10, 1 },
        { Tag("WB", "RESIN"), 2, 10, 1 },
        { Tag("RESIN", "R_CURE"), 1, 20, 1 },
        { Tag("RESIN", "R_CURE"), 2, 25, 1 },
        { Tag("RESIN", "R_CURE"), 3, 25, 1 },
        { Tag("RESIN", "R_CURE"), 4, 20, 1 },
        { Tag("R_CURE", "PLASMA"), 1, 25, 4 }
    };

    for (size_t i = 0; i < line.size(); i++){
        line[i].pos = ProcessPos[i];
    }

    vector<Lot> product(N);

    char filename[50];
    ofstream ofs("drawParam.txt");
    ofs << "T_END = " << T << endl;
    ofs << "timeStep = " << timeStep << endl;
    ofs.close();

    for (int i = 0; i <= T; i += timeStep){
        cout << "T = " << i << endl << endl; // time stamps

        //show lot status
        cout << "---------- All Lots Status ----------" << endl;
        cout << "\t" << "qty" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;
        for (auto &lot : product){
            lot.showStatus();
        }
        cout << "-------------------------------------" << endl << endl;

        //show & output in-process status
        sprintf(filename, "./res/inPrc%03d.txt", i);
        ofs.open(filename);

        cout << "---- in-Process Status ----" << endl;
        for (auto &prc : Process::inProcess){
            cout << prc.name << "\t\t" << prc.num << " lot" << endl;
        }
        cout << "---------------------------" << endl << endl;
        Process::outputInProcess(ofs);
        ofs.close();


        //show & output process status
        sprintf(filename, "./res/prc%03d.txt", i);
        ofs.open(filename);

        cout << "---------- Process Status ------------" << endl;
        cout << "name" << "\t" << "No." << "\t";
        cout << "next" << "\t" << "capa" << "\t" << "isUsed?" << "\t";
        cout << "lot No." << endl;
        for (auto &prc : line){
            prc.showStatus();
            prc.fileOutput(ofs);
        }
        cout << "--------------------------------------" << endl << endl;
        ofs.close();

        for (auto &prc : line){
            if (!prc.isUsed){
                if (prc.hasInProcess()){
                    prc.lotStart(product);
                }
            }
            else{
                prc.update();
                if (prc.time >= prc.processTime){
                    prc.lotEnd(product);
                }
            }
        }

        cout << endl << endl;
    }

    return 0;
}