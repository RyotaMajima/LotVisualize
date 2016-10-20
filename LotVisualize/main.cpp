#include "define.h"
#include "header.h"

int main(){
    vector<Lot> product(N);
    //Process DB("DB", "WB", 15);

    vector<Process> line{ { "DB", "WB", 15 }, { "WB", "RESIN", 10 }, {"RESIN", "MOLD", 20} };
    
    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;

        //show lot state
        for (auto &lot : product){
            lot.showStatus();
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