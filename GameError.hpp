//
//  GameError.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 10/26/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#ifndef GameError_hpp
#define GameError_hpp
#include "tools.hpp"
class GameError{
    public:
    GameError() = default;
    virtual ~GameError() {cout << "Default virtual destructor is called "<<endl;}
    virtual void print(){
     cout  << "Error in your game logic" <<endl;
    }
};
//-----------------------------------------------------------------------------
class WrongGameType : public GameError{
    char k;
public:
    WrongGameType(char p){k = p;}
   
    virtual void print(){
        cerr << "You have entered: " << k << "Which is wrong game type" <<endl;
    }
};
//-----------------------------------------------------------------------------
class WrongBoardInput : public GameError{
public:
    WrongBoardInput() = default;
    virtual void print(){ cerr << "Error because valid input should be from 1 through N." <<endl; }
};
//-----------------------------------------------------------------------------
class ExtraJunkInput : public GameError{
public:
   
    virtual void print() {cerr << " Extra row or column than required "<< endl;}
};
//----------------------------------------------------------------------------
class WrongRowOrColumn : public GameError{
public:
    WrongRowOrColumn() = default;
    virtual void print() {cerr << "Row number or column number should be only from 1 through 9";}
};
//----------------------------------------------------------------------------
class Emptystack : public GameError{
public:
    Emptystack() = default;
   
    virtual void print() {cerr << "Empty stack, cannot get top element";}
};
//----------------------------------------------------------------------------
class Inputmismatch : public GameError{
public:
    Inputmismatch() = default;
    virtual void print() {cerr << "Input type mismatch error occures" <<endl;}
};
#endif /* GameError_hpp */
