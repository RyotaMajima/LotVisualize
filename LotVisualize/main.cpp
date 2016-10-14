#include <iostream>
#include <vector>

using namespace std;

class Lot{
public:
    int pcs;
    int time;

public:
    Lot();
};

Lot::Lot(){
    cout << "constructor" << endl;
}

int main(){

    Lot lot;
    vector<Lot> lots(5);

    return 0;
}