#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <iomanip>

using namespace std;

const int T = 70;
const int timeStep = 5;
const int N = 4;

const vector<string> NAME{ "DB", "CURE", "WB", "RESIN", "CURE"};
const vector<tuple<string, int>> INFO{
        make_tuple("DB", 15), make_tuple("CURE", 30),
        make_tuple( "WB", 10), make_tuple("RESIN", 50),
        make_tuple("CURE", 45) };