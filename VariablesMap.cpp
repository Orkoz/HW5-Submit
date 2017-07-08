#include"VariablesMap.h"
#include"ScriptExceptions.h"

using namespace std;

//*************************************************************************
//* Function name: VariablesMap
//* Description: empty contractor – sets the Saved Var name in the valid characters.
//* Parameters: none.
//* Return Value: none.
//*************************************************************************

VariablesMap::VariablesMap(): SavedName_("_saved"){}

//*************************************************************************
//* Function name: ~SetSavedName
//* Description: change the Saved Var name
//* Parameters:
//*		newSavedName – string type – the new Saved Var name.
//* Return Value: none.
//*************************************************************************

void VariablesMap::SetSavedName(const string& newSavedName){
    SavedName_ = newSavedName;
}


//*************************************************************************
//* Function name: Operator[]
//* Description: if ‘x’ is a valid variable name (start with one of the ABC and all characters are in the valid characters list) then returns a new Variable referance.
//* Parameters:
//*		x – string type – the name of the new variable in the map object.
//* Return Value: VarPtr reference.
//*************************************************************************

VarPtr& VariablesMap::operator[](const string & x){

	int i,j;
	for (i = 0; i < x.size(); i++) {
		for (j = 0; j <= 64; j++) {
			if (j == 64 || (i == 0 && j > 51))
				throw INVALID_VAR_NAME(x);
			if (x[i] == VALID_VAR_CHARS[j])
				break;
		}
	}

    return StringToVarMap_[x];
}


//*************************************************************************
//* Function name: erase
//* Description: erases the element with the name ‘x’
//* Parameters:
//*		x – string type – the name of the variable to be deleted.
//* Return Value: none.
//*************************************************************************

void VariablesMap::erase(const string & x){
	StringToVarMap_.erase(x);
}


//*************************************************************************
//* Function name: ClearTmpVars
//* Description: go throw the tmp variable list (a list which contain all the tmp variable names) and delete the match variable from the map.
//* Parameters: none.
//* Return Value: none.
//*************************************************************************

void VariablesMap::ClearTmpVars(){
	unsigned int i;
    for (i = 0; i < tmpVarList_.size(); ++i) {
        StringToVarMap_.erase(tmpVarList_[i]);
    }
    tmpVarList_.clear();
}


//*************************************************************************
//* Function name: at
//* Description: returns a reference to the Variable which ‘x’ is map to if x is a valid variable name.
//* Parameters:
//*		x – string type – the name of the variable in the map object.
//* Return Value: VarPtr reference.
//*************************************************************************

VarPtr& VariablesMap::at(const string & x){
    return StringToVarMap_.at(x);
}


//*************************************************************************
//* Function name: GetTmpVariable
//* Description: finds a free valid variable name (start with one of the ABC and all characters are in the valid characters list).
//* Parameters: none.
//* Return Value: string type – the new variable name.
//*************************************************************************

//*************************************************************************
//* checks if ‘a’ is free, then checks ‘b’ and so on.
//* if none of the ABC is free check ‘aa’ then ‘ab’..’ba’ , ‘bb’ and so on.
//* in the end go throw all 3 characters combination that following the valid name rules.
//*************************************************************************

string VariablesMap::GetTmpVariable() {
    int i, j, k;
    string key_guess;
    bool found = false;
    for (i = 0; i < 53; ++i) {
        key_guess = VALID_VAR_CHARS[i];
        if ((key_guess != SavedName_) && (StringToVarMap_.find(key_guess) == StringToVarMap_.end())){
            found = true;
            break;
        }
    }

    if (!found){
        for (i = 0; i < 53; ++i) {
            key_guess = VALID_VAR_CHARS[i];
            for (j = 0; j < 64; ++j) {
                key_guess += VALID_VAR_CHARS[j];
                if ((key_guess != SavedName_) && (StringToVarMap_.find(key_guess) == StringToVarMap_.end())){
                    found = true;
                    i = 52;
                    break;
                }
            }
        }
    }

    if (!found){
        for (i = 0; i < 53; ++i) {
            key_guess = VALID_VAR_CHARS[i];
            for (j = 0; j < 64; ++j) {
                key_guess += VALID_VAR_CHARS[j];
                for (k = 0; k < 64; ++k)
                    key_guess += VALID_VAR_CHARS[k];
                    if ((key_guess != SavedName_) && (StringToVarMap_.find(key_guess) == StringToVarMap_.end())){
                        found = true;
                        i=52;
                        j=64;
                        break;
                    }
                }
            }
        }


    tmpVarList_.push_back(key_guess);
    StringToVarMap_[key_guess] = *(new VarPtr());
    return key_guess;
}
