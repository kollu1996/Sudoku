//
//  Frame.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 11/18/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#ifndef Frame_hpp
#define Frame_hpp
#include "tools.hpp"
#include "State.hpp"
class Frame {
    State* stobject;   //I can also use vector, since it is dynamic
    int p;
public:
    Frame(State stobj[], int N) {
        p = N;
        stobject = new State[N*N];
        for(int k=1; k<=N*N; k++){
            stobject[k-1] = stobj[k-1];
        }
    }
    Frame() = default;
    ~Frame() {delete [] stobject;};
    State* getFrames() {return stobject;}
    void serialize(ofstream& file);
    void realize(ifstream& file);
    void printframe();
    State& operator [] (int k){cout << "I am used"; return stobject[k]; }
};
#endif /* Frame_hpp */
