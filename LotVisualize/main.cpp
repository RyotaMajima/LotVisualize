#include "define.h"
#include "header.h"

int main(){
    vector<Lot> product(N);
    Process DB("DB", "WB", 15);

    for (int i = 0; i < T; i += timeStep){
        cout << "T = " << i << endl; // time stamps
        cout << "\t" << "pcs" << "\t" << "current" << "\t";
        cout << "next" << "\t" << "now?" << endl;

        for (auto &lot : product){
            lot.showData();
        }

        if (DB.isUsed == false){
            DB.lotStart(product);
        }
        else{
            DB.update();
            if (DB.time >= DB.processTime){
                DB.lotEnd(product);
            }
        }

        cout << endl << endl;
    }

    return 0;
}