#include <iostream>
#include <vector>

#include "define.h"
#include "header.h"


int main(){

    vector<Lot> lots(5);
    vector<State> lotStates(5);

    Process DB;

    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl << endl;

        if (DB.isEmpty){
            for (int j = 0; j < lots.size(); j++){

            }
        }

    }


    return 0;
}