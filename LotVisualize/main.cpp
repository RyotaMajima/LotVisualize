#include "define.h"
#include "header.h"

int main(){
    vector<Process> line{
        //{ name, nextName, MachineNo, pos_x, pos_y}
        { "DB", "DB_CURE", 1, 5, 1.0, 16.0 },
        { "DB", "DB_CURE", 2, 10, 1.0, 13.0 },
        { "DB_CURE", "WB", 1, 15, 16.0, 12.0 },
        { "DB_CURE", "WB", 2, 15, 16.0, 9.0},
        { "WB", "RESIN", 1, 10, 1.0, 9.0 },
        { "WB", "RESIN", 2, 10, 1.0, 6.0 },
        { "RESIN", "RESIN_CURE", 1, 20, 1.0, 1.0 },
        { "RESIN", "RESIN_CURE", 2, 25, 4.0, 1.0 },
        { "RESIN", "RESIN_CURE", 3, 25, 1.0, -3.0 },
        { "RESIN", "RESIN_CURE", 4, 20, 4.0, -3.0 },
        { "RESIN_CURE", "PLASMA", 1, 25, 10, -8 }
    };
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
        cout << "\t" << "qty" << "\t" << "curt" << "\t";
        cout << "next" << "\t" << "now?" << endl;
        for (auto &lot : product){
            lot.showStatus();
        }
        cout << "-------------------------------------" << endl << endl;

        //show & output in-process status
        sprintf(filename, "./output/inProcess%03d.txt", i);
        ofs.open(filename);

        cout << "--- in-Process Status ---" << endl;
        for (auto &prc : Process::inProcess){
            cout << get<0>(prc) << "\t\t" << get<1>(prc) << " lot" << endl;
        }
        cout << "--------------------------" << endl << endl;
        Process::outputInProcess(ofs);
        ofs.close();


        //show & output process status
        sprintf(filename, "./output/output%03d.txt", i);
        ofs.open(filename);

        cout << "---------- Process Status ------------" << endl;
        cout << "name" << "\t" << "No." << "\t";
        cout << "next" << "\t" << "isUsed?" << "\t";
        cout << "lot No." << endl;
        for (auto &prc : line){
            prc.showStatus();
            prc.output(ofs);
        }
        cout << "--------------------------------------" << endl << endl;
        ofs.close();

        for (auto &prc : line){
            if (!prc.isUsed){
                if (prc.hasNext()){
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