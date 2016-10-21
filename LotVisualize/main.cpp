#include "define.h"
#include "header.h"

int main(){
    vector<Lot> product(N);
    vector<Process> line{
        { "DB", "CURE", 1, 15 },
        {"DB", "CURE", 2, 15},
        {"CURE", "WB", 1, 50},
        { "WB", "RESIN", 1, 10 },
        {"RESIN", "MOLD", 1, 20} };
    
    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;

        //show lot status
        for (auto &lot : product){
            lot.showStatus();
        }
        cout << endl;

        cout << "name" << "\t" << "M/C No." << "\t";
        cout << "next" << "\t" << "isUsed?" << "\t";
        cout << "lot No." << endl;

        //show process status
        for (auto &prc : line){
            prc.showStatus();
        }
        cout << endl;

        for (int j = 0; j < (int)line.size(); j++){
            if (line[j].isUsed){
                line[j].update();
                if (line[j].time >= line[j].processTime){
                    line[j].lotEnd(product);
                }
            }
            else{
                line[j].lotStart(product);
            }
        }

        cout << endl << endl;
    }

    return 0;
}