#include "define.h"
#include "header.h"

int main(){
    vector<Process> line{
        { "DB", "DB_CURE", 1, 5 },
        { "DB", "DB_CURE", 2, 10 },
        { "DB_CURE", "WB", 1, 15 },
        { "WB", "RESIN", 1, 10 },
        { "RESIN", "MOLD", 1, 20 }
    };
    vector<Lot> product(N);
    
    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl << endl; // time stamps

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
    }

    return 0;
}