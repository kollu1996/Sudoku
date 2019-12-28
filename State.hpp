//
//  State.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 9/17/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//


#ifndef State_hpp
#define State_hpp

#include "tools.hpp"
#include "GameError.hpp"

//======================== State Class =========================================
class Cluster;
class State{

private:
    short possiblities = 0x3fe;
    char value = '-';
    bool fixed = false;
    bool markpossible( short int a );
   
public:
    State(){};
    State( char v );
    State(char v, bool f, short possiblities ){
        value = v;
        fixed = f;
        this->possiblities = possiblities;
    }
    State( const State& st );
    ~State() {};
    size_t vector_size;
    void mark ( char ch );
    char getValue() const { return value; }
    short getposlst() const { return possiblities; }
    bool getfixed() const { return fixed; }
    ostream& stprint( ostream& strobj );
    void updateposlist(const int k);
   
};

//=========================== Square class =====================================
class Square{
    State stobj;
    short int row;
    short int column;
    vector <Cluster*> clues;
public:
    Square() = default;
    Square( char ch, short int row, short int column ) : stobj( ch ), row(row), column(column){};
    void mark( char v ){
        stobj.mark( v );
    };
    ~Square() = default;
    ostream& sqprint( ostream& squareobj );
    void addCluster(Cluster* clus) {clues.push_back(clus);}
    void sqrshoop();
    void turnOff(const int p){stobj.updateposlist(p);}
    const char getval() {return stobj.getValue();}
    const short getposslst() {return stobj.getposlst();}
    State& getstateobj() {return stobj;}
};

//==============================================================
inline ostream& operator<<(ostream& st, State& s){return s.stprint(st);}
inline ostream& operator<<(ostream& st, Square& sq){return sq.sqprint(st);}
#endif /* State_hpp */

