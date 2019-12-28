//
//  State.cpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 9/17/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#include "State.hpp"
#include "Cluster.hpp"
//========================================================================
//Pre Condition: Initializes the instance variables to default values
//Post Condition: Validates the parameter and changes the default variables
State::State( char v ){
    if(isdigit(v)){
        possiblities = 0;
        fixed = true;
        value = v;
    }
}
//=========================================================================
//Pre Condition: Copy constructor for state
State::State(const State& st){
    value = st.getValue();
    possiblities = st.getposlst();
    fixed = st.getfixed();
}
//=========================================================================
//Pre Condition: Checks the possiblity list
//Post Condition: If marking is possible it marks and if marked makes
//possiblity list to zero
void
State :: mark( char ch ){
    short int k;
    k = ch - '0';
    if((k<0 || k >10) && ch!= '-'){
        throw WrongBoardInput();
    }
    int maskoutput;
    short mask = 0x001;
    unsigned short int temp = possiblities;
    temp  >>= k;
    maskoutput = mask & temp;
    if(maskoutput == 1){
        value = ch;
        possiblities = 0;
    }
    else{cout <<"There is no possiblity"<<"\n";}
}
//========================================================================
//Pre Condition: To print State class
//Post Condition: Uses mask operation
ostream&
State :: stprint( ostream& strobj ){
    string str1;
    unsigned short int temp = possiblities;
    short mask = 0x001;
    int maskoutput;
    int p;
    if(vector_size == 4) p = 6;
    else p = 9;
    strobj  << value << " ";
    strobj << fixed << " ";
    strobj << possiblities << " ";
    for( int k=1; k<= p; k++ ){
        temp >>= 1;
        maskoutput = mask & temp;
        if( maskoutput == 1 ){
            cout << k;
        }
        else if ( maskoutput == 0  ){
            cout <<'-';
        }
    }
    cout << "\n";
    return strobj;
}
//=============================================================
//Pre Condition: To print Square Class
//Post Condition: Delegates print function in state class
ostream&
Square :: sqprint( ostream& squareobj ){
    squareobj <<"["<< "ROW:"<<" "<< row <<" "<<","<< "COLUMN:"<<" "<<column<<"]"
    << " ";
    stobj.vector_size = clues.size();
    squareobj << stobj;
    return squareobj;
}
//=========================================================
//Precondition: To shoop value in square from all its corresponding clusters
//Postcondition: Delegates the action to cluster class by passing value in it
void
Square:: sqrshoop(){
    vector <Cluster*> :: iterator ptr;
    for(ptr = clues.begin(); ptr < clues.end(); ptr++){
        (*ptr)->shoopcltr(stobj.getValue());
    }
}
//=========================================================
//Precondition: To remove the bit corresponding to value from pos list
//Postcondition: Uses mask operation to check if bit value is 1, if so updates to 0
void
State::updateposlist(const int j){
    short mask = 0x001;
    unsigned short int temp = possiblities;
    int maskoutput;
    temp >>= j;
    maskoutput = mask & temp;
    if(maskoutput == 1){
        int p = mask << j;
        possiblities = possiblities -  p;
    }
}
