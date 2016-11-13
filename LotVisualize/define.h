#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

const int T = 300;
const int timeStep = 1;
const int N = 12;

const vector<string> ProcessName{
    "DB", "DB_CURE", "WB", "RESIN", "R_CURE",
    "PLASMA", "MOLD", "MARK", "DICING", "DIC_CURE",
    "TPG"};

const vector<int> NumOfMachine{
    2, 2, 2, 4, 4, 1, 2, 1, 2, 1, 2 };
