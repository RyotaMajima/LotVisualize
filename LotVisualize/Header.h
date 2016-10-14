#pragma once

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
