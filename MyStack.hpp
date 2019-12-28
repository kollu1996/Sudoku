//
//  MyStack.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 11/21/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//

#ifndef MyStack_hpp
#define MyStack_hpp
#include "tools.hpp"
#include "Frame.hpp"
class MyStack : private vector <Frame*> {
private:
    vector <Frame*> v;
public:
    MyStack() = default;
    ~MyStack(){
        for(Frame* f: v){ delete f;}
    }
    void pop() {
        if (v.size() == 0) cout << "Empy vector, cannot pop";
        v.vector::pop_back();
    }
    Frame* stack_top() {return v.vector::back();}
    void push( Frame *f ){ v.vector::push_back(f);}
    int size() {return  v.vector::size();}
    void zap() {while(v.vector::size() > 0){v.vector::pop_back();}}
};

#endif /* MyStack_hpp */
