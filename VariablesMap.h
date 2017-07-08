#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_
#include <map>
#include <string>
#include <vector>
#include "Variable.h"


#define VALID_VAR_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

using namespace std;


class VariablesMap
{
public:
	VariablesMap();
	void SetSavedName(const string& NewSavedName);
	string GetTmpVariable();
	void ClearTmpVars();
	VarPtr& operator[](const string& x);
	VarPtr& at(const string& x);
	void erase(const string& x);

private:
    map<string,VarPtr> StringToVarMap_;
	string SavedName_;
    vector<string> tmpVarList_;
};
#endif // _VARIABLES_MAP_H_
