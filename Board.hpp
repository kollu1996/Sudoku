//
//  Board.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 9/21/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#ifndef Board_hpp
#define Board_hpp
#include "tools.hpp"
#include "State.hpp"
#include "GameError.hpp"
#include "StreamError.hpp"
#include "CanView.hpp"
#include "Frame.hpp"
#include "MyStack.hpp"
#include <typeinfo>

class Cluster;
class Board: public CanView{
protected:
    const int N;
    void createBox(const short j, const short k);
    void createSixyHBox(const short j, const short k);
    void createSixyVBox(const short j, const short k);
    void createDiagonalOne();
    void createDiagonalTwo();
    void callShoop();

private:
    Square *bd;
    ifstream& file;
    short int left;
    int *k;
    vector <Cluster*> clue;
    void getpuzzle();
    void makeClusters();
    void createRow(const short j);
    void createColumn(const short j);
    const bool validate(const char k);
    void checkfile();
    void readcontents();
    
    
public:
    ~Board();
    Board(int n, ifstream& puzfile) : N(n), file(puzfile){
        bd = new Square[N*N];
        getpuzzle();
        makeClusters();
    };
    Frame*  move();
    void markBoard();
    void restoreState(Frame* f);
    void Turnoffpolist();
    void printFrame(Frame* f);
    Square& sub(const int j, const int k);
    Square& sub1( int j, int k) const;
    ostream& print1(ostream& ofs);
    // Implementing virtual functions from can view
      char getMarkChar( int row,  int col) const{
        Square s = sub1(row, col);
        return s.getval();
      }
       string getPossibilityString(int row, int col) const{
        short temp;
        string st = "";
        short mask = 0x001;
        int maskoutput;
        Square s = sub1(row, col);
         temp = s.getposslst();
         for( int k=1; k<=N; k++ ){
             temp >>= 1;
             maskoutput = mask & temp;
             if( maskoutput == 1 ){
                 st += '0'+ k;
             }
             else if ( maskoutput == 0  ){
                 st = st + '-';
             }
         }
          while(st.length() < 9){
              st = st + " ";
          }
         return st;
    }
};
inline ostream& operator<<(ostream& st, Board& b){return b.print1(st);}
//===================================================================
class TradBoard : public Board{
public:
    TradBoard(int n, ifstream& puzfile): Board(n, puzfile){
        createboxclusters();
         callShoop();
    }
    void createboxclusters();
    ~TradBoard() = default;
};
//===================================================================
class DiagBoard : public TradBoard{
public:
    DiagBoard(int n, ifstream& puzfile): TradBoard(n, puzfile){
        creatediagaonalclusters();
         callShoop();
    }
    void creatediagaonalclusters();
    ~DiagBoard() = default;
};
//===================================================================
class SixyBoard : public Board{
public:
    SixyBoard(int n, ifstream& puzfile):  Board(n, puzfile){
        createHboxcluster();
        createVboxcluster();
        callShoop();
    }
public:
    void createHboxcluster();
    void createVboxcluster();
    ~SixyBoard() = default;
};
#endif /* Board_hpp */
