#include <iostream>
#include <vector>

#include "define.h"
#include "header.h"


int main(){

    vector<Lot> lots(5);
    vector<State> lotStates(5);

    Process DB;

    for (int i = 0; i < T; i += timeStep){
        for (int j = 0; j < lots.size(); j++){
            if (lots[j].nowProcess) lots[j].time += timeStep;
        }

        cout << "T = " << i << endl << endl; // time stamps

        cout << "No." << "\t" << "current process" << endl;
        for (int j = 0; j < lots.size(); j++){
            cout << j << "\t" << lotStates[j].currentProcess << endl;
        }

        if (DB.isEmpty){
            int index = 0;
            for (int j = 0; j < lots.size(); j++){
                if (lotStates[j].currentProcess == _Wafer && lotStates[j].nextProcess == _DB){
                    index = j;
                    break;
                }
            }

            lotStates[index].currentProcess = _DB;
            lots[index].nowProcess = true;
            DB.isEmpty = false;

        }
        else{
            for (int j = 0; j < lots.size(); j++){
                if (lotStates[j].currentProcess == _DB){
                    if (lots[j].time >= DB.processTime){
                        lotStates[j].currentProcess = 10;
                        lotStates[j].nextProcess = _WB;
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