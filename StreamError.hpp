//
//  StreamError.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 10/24/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#ifndef StreamError_hpp
#define StreamError_hpp
#include "tools.hpp"
class StreamError{
    string filname;
public:
    StreamError() = default;
    virtual ~StreamError() {cout << "I am a default virtual destructor" <<endl;}
    virtual void print(){
     cerr << "There is an error in your input" <<endl;
    }
};

class WrongFilname : public StreamError{
public:
    WrongFilname() = default;
    virtual void print(){
        cerr << "You have entered a wrong filename. " <<endl;
    }
};

class NoFilgiven : public StreamError{
public:
    NoFilgiven() = default;
    
    virtual void print(){
        cerr << "You have not entered any file. " <<endl;
    }
};

class Badfile : public StreamError{
    public:
    Badfile() = default;
    virtual void print(){
        cerr << "File did not meet sudoku board input specification"<<endl;
    }
};

class BlankFile : public StreamError{
    public:
    BlankFile() = default;
    virtual void print(){
        cerr << "No content found in the file"<<endl;
    }
};
#endif /* StreamError_hpp */
