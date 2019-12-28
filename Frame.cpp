//
//  Frame.cpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 11/18/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#include "Frame.hpp"
#include "StreamError.hpp"
//Writes all state objects to a file.
void
Frame:: serialize(ofstream& file){
    for(int k=1; k<= p*p; k++){
        file << stobject[k-1] << "  " << "\n";
    }
}
//============================================================
//Reads each state object from the file and creates a new Frame
void
Frame:: realize(ifstream& file){
    State *stateobject = new State[p*p];
    char v;
    bool f;
    short q;
    int m = 1;
     while(!file.eof()){
         file >> v >> f >> q;
         State *s = new State(v,f,q);
         stateobject[m-1] = *s;
         m+=1;
    }
    this->stobject = stateobject;
}
//============================================================
void
Frame:: printframe(){                                       //Just for debugging
    for(int i = 0; i< p*p; i++){
        cout << stobject[i];
    }
}

