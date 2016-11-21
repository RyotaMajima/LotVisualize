#include "define.h"
#include "header.h"

const vector<Position> ProcessPos{
    { -22.0, 14.0 }, { -22.0, 11.0 },
    { -17.0, 14.0 }, { -17.0, 11.0 },
    { -7.0, 14.0 }, { -7.0, 11.0 },
    { -1.0, 14.0 }, { -1.0, 11.0 }, { 2.0, 14.0 }, { 2.0, 11.0 },
    { 12.0, 14.0 }, { 12.0, 11.0 }, { 18.0, 14.0 }, { 18.0, 11.0 },
    { 21, -3 },
    { 21, -10 }, { 21, -13 },
    { 11, -20 },
    { -7, -20 }, { -4, -20 },
    { -15, -20 }, { -15, -20 }, { -15, -20 }, { -15, -20 },
    { -15, -20 }, { -15, -20 }, { -15, -20 }, { -15, -20 },
    { -21, -3 }, {-21, -6}
};

int main(){
    vector<Process> line{
        //{ tag, MachineNo, processTime, capacity }
        { Tag("DB", "DB_CURE"), 1, 6, 1 },
        { Tag("DB", "DB_CURE"), 2, 6, 1 },
        { Tag("DB_CURE", "WB"), 1, 15, 3 },
        { Tag("DB_CURE", "WB"), 2, 15, 3 },
        { Tag("WB", "RESIN"), 1, 5, 1 },
        { Tag("WB", "RESIN"), 2, 5, 1 },
        { Tag("RESIN", "R_CURE"), 1, 30, 1 },
        { Tag("RESIN", "R_CURE"), 2, 30, 1 },
        { Tag("RESIN", "R_CURE"), 3, 30, 1 },
        { Tag("RESIN", "R_CURE"), 4, 30, 1 },
        { Tag("R_CURE", "PLASMA"), 1, 30, 4 },
        { Tag("R_CURE", "PLASMA"), 2, 30, 4 },
        { Tag("R_CURE", "PLASMA"), 3, 30, 4 },
        { Tag("R_CURE", "PLASMA"), 4, 30, 4 },
        { Tag("PLASMA", "MOLD"), 1, 4, 1 },
        { Tag("MOLD", "MARK"), 1, 5, 1 },
        { Tag("MOLD", "MARK"), 2, 6, 1 },
        { Tag("MARK", "DICING"), 1, 3, 1 },
        { Tag("DICING", "DIC_CURE"), 1, 9, 1 },
        { Tag("DICING", "DIC_CURE"), 2, 9, 1 },
        { Tag("DIC_CURE", "TPG"), 1, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 2, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 3, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 4, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 5, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 6, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 7, 30, 1 },
        { Tag("DIC_CURE", "TPG"), 8, 30, 1 },
        { Tag{"TPG", "REEL"}, 1, 12, 1 },
        { Tag{"TPG", "REEL"}, 2, 11, 1 }
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

    for (int i = 1; i <= T; i += timeStep){
        cout << "T = " << i << endl << endl; // time stamps

        if (i % 30 == 0){
            for (int j = 0; j < 12; j++){
                product.push_back(Lot());
            }
        }

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
            cout << prc.name << "\t\t" << prc.dq.size() << " lot" << ": ";
            for (auto &val : prc.dq){
                cout << val << " ";
            }
            cout << endl;
        }
        cout << "---------------------------" << endl << endl;
        Process::outputInProcess(ofs, product);
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
            prc.update(product);
     
            //if (prc.state == State::WAIT){
            //    if (prc.hasInProcess()){
            //        prc.lotStart(product);
            //    }
            //}
            //else{
            //    prc.update();
            //    if (prc.time >= prc.processTime){
            //        prc.lotEnd(product);
            //    }
            //}
        }

        cout << endl << endl;
    }

    return 0;
}