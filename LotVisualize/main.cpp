#include "define.h"
#include "header.h"

int main(){
    vector<Lot> product(N);
    //vector<Process> line{ { "DB", "WB", 15 }, { "WB", "RESIN", 10 }, {"RESIN", "MOLD", 20} };

    vector<Process> line;

    int index = 0;
    for (int i = 0; i < (int)INFO.size()-1; i++){
        index = i;
        line.emplace_back(get<0>(INFO[index]), get<0>(INFO[index+1]), get<1>(INFO[index]), get<2>(INFO[index]));
    }

    vector<vector<Process>> test((int)INFO.size(), vector<Process>());

    for (int i = 0; i < (int)test.size(); i++){
        for (int j = 0; j < get<1>(INFO[i]); j++){
            test[i].emplace_back(get<0>(INFO[index]), get<0>(INFO[index + 1]), j, get<2>(INFO[index]));
        }
    }
    
    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;

        //show lot status
        for (auto &lot : product){
            lot.showStatus();
        }
        cout << endl;

        cout << "name" << "\t" << "next" << "\t" << "isUsed?" << "\t";
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