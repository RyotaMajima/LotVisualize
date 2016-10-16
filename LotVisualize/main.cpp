#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "define.h"
#include "header.h"

int main(){

    vector<Lot> lots(N);
    Process DB("DB", 15);

    for (int i = 0; i < T; i += timeStep){
        for (int j = 0; j < N; j++){
            if (lots[j].nowProcess) lots[j].time += timeStep;
        }

        cout << "T = " << i << endl << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;
        for (int j = 0; j < N; j++){
            lots[j].showData();
        }

        if (DB.isUsed == false){
            DB.lotStart(lots);
            //int index = 0;
            //for (int j = 0; j < N; j++){
            //    if (lots[j].current == "None" && lots[j].next == "DB"){
            //        index = j;
            //        cout << "lot " << index << "\t" << "DB start." << endl;
            //        break;
            //    }
            //}

            //lots[index].current = "DB";
            //lots[index].nowProcess = true;
            //DB.isUsed = true;
        }
        else{
            for (int j = 0; j < N; j++){
                if (lots[j].current == "DB"){
                    if (lots[j].time >= DB.processTime){
                        lots[j].current = "None";
                        lots[j].next = "WB";
                        lots[j].nowProcess = false;
                        DB.isUsed = false;
                        cout << "lot " << j << "\t" << "DB end." << endl;
                    }
                    break;
                }
            }
        }

        cout << endl;
    }

    return 0;
}