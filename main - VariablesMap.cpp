#include<iostream>
#include "VariablesMap.h"

using namespace std;



int main() {
    VariablesMap map;
    map.SetSavedName("Or");
    string x = map.GetTmpVariable();
    x = map.GetTmpVariable();
    *(map["a"]) = 3;
+
    VarPtr p2(map.at("a"));
    *(map["ab"]) = 3;
    map.ClearTmpVars();
	return 0;
};
