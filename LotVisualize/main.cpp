#include "define.h"
#include "header.h"

int main(){
    vector<Lot> lots(N);
    Process DB("DB", "WB", 15);

    for (int i = 0; i < T; i += timeStep){
        for (int j = 0; j < N; j++){
            if (lots[j].nowProcess) lots[j].time += timeStep;
        }

        cout << "T = " << i << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;

        for (int j = 0; j < N; j++){
            lots[j].showData();
        }

        if (DB.isUsed == false){
            DB.lotStart(lots);
        }
        else{
            DB.update();
            if (DB.time >= DB.processTime){
                DB.lotEnd(lots);
            }
        }

        cout << endl << endl;;
    }

    return 0;
}