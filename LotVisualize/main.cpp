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

        cout << "No." << "\t" << "current process" << endl;
        for (int j = 0; j < N; j++){
            cout << j << "\t" << lots[j].current << endl;
        }

        if (DB.isEmpty){
            int index = 0;
            for (int j = 0; j < N; j++){
                if (lots[j].current == _Wafer && lots[j].next == _DB){
                    index = j;
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
                        lots[j].current = 10;
                        lots[j].next = _WB;
                        DB.isEmpty = true;
                    }

                    break;
                }
            }
        }

        cout << endl;
    }


    return 0;
}