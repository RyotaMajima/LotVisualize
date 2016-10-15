#include <iostream>
#include <vector>

#include "define.h"
#include "header.h"

int main(){

    vector<Lot> lots(N);
    Process DB;

    for (int i = 0; i < T; i += timeStep){
        for (int j = 0; j < N; j++){
            if (lots[j].nowProcess) lots[j].time += timeStep;
        }

        cout << "T = " << i << endl << endl; // time stamps

        cout << "No." << "\t" << "current" << "\t" << "time" << endl;
        for (int j = 0; j < N; j++){
            cout << j << "\t" << lots[j].current << "\t" << lots[j].time << endl;
        }

        if (DB.isEmpty){
            int index = 0;
            for (int j = 0; j < N; j++){
                if (lots[j].current == _Wafer && lots[j].next == _DB){
                    index = j;
                    cout << "lot " << index << "\t" << "DB start." << endl;
                    break;
                }
            }

            lots[index].current = _DB;
            lots[index].nowProcess = true;
            DB.isEmpty = false;
        }
        else{
            for (int j = 0; j < N; j++){
                if (lots[j].current == _DB){
                    if (lots[j].time >= DB.processTime){
                        lots[j].current = _None;
                        lots[j].next = _WB;
                        lots[j].nowProcess = false;
                        DB.isEmpty = true;
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