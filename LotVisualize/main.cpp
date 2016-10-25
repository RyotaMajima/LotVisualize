#include "define.h"
#include "header.h"

int main(){
    vector<Process> line{
        { "DB", "DB_CURE", 1, 5, 1.0, 11.0 },
        { "DB", "DB_CURE", 2, 10, 1.0, 8.0 },
        { "DB_CURE", "WB", 1, 15, 11.0, 6.0 },
        { "WB", "RESIN", 1, 10 , 1.0, 4.0 },
        { "RESIN", "MOLD", 1, 20, -10.0, -5.0 }
    };
    vector<Lot> product(N);

    char filename[50];
    ofstream ofs;
    
    for (int i = 0; i <= T; i += timeStep){
        cout << "T = " << i << endl << endl; // time stamps
        sprintf(filename, "./output/output%03d.txt", i);
        ofs.open(filename);

        //show lot status
        cout << "---------- All Lots Status ----------" << endl;
        cout << "\t" << "qty" << "\t" << "curt" << "\t";
        cout << "next" << "\t" << "now?" << endl;
        for (auto &lot : product){
            lot.showStatus();
        }
        cout << "-------------------------------------" << endl << endl;

        //show in-process status
        cout << "--- in-Process Status ---" << endl;
        for (auto &pair : Process::inProcess){
            cout << pair.first << "\t\t" << pair.second << " lot" << endl;
        }
        cout << "--------------------------" << endl << endl;

        //show process status
        cout << "---------- Process Status ------------" << endl;
        cout << "name" << "\t" << "No." << "\t";
        cout << "next" << "\t" << "isUsed?" << "\t";
        cout << "lot No." << endl;
        for (auto &prc : line){
            prc.showStatus();
            prc.output(ofs);
        }
        cout << "--------------------------------------" << endl << endl;


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
        ofs.close();
    }

    return 0;
}