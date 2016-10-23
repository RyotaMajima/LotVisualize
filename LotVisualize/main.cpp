#include "define.h"
#include "header.h"

int main(){
    vector<Lot> product(N);
    vector<Process> line{
        { "DB", "DB_CURE", 1, 15 },
        { "DB", "DB_CURE", 2, 15 },
        { "DB_CURE", "WB", 1, 50 },
        { "WB", "RESIN", 1, 10 },
        { "RESIN", "MOLD", 1, 20 } };
    
    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;

        //show lot status
        for (auto &lot : product){
            lot.showStatus();
        }
        cout << endl;

        //show in-process status
        cout << "-----in-progress status-----" << endl;
        for (auto &pair : Process::inProcess){
            cout << pair.first << "\t\t" << pair.second << " lot" << endl;
        }
        cout << endl;

        //show process status
        cout << "name" << "\t" << "M/C No." << "\t";
        cout << "next" << "\t" << "isUsed?" << "\t";
        cout << "lot No." << endl;
        for (auto &prc : line){
            prc.showStatus();
        }
        cout << endl;

        for (auto &prc : line){
            if (prc.isUsed){
                prc.update();
                if (prc.time >= prc.processTime){
                    prc.lotEnd(product);
                }
            }
            else{
                prc.lotStart(product);
            }
        }

        cout << endl << endl;
    }

    return 0;
}