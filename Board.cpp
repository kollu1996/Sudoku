//
//  Board.cpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 9/21/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#include "Board.hpp"
#include "Cluster.hpp"
static const char* cltrtype [] = {"Box", "Row", "Column", "DIAG"};
//=========================================
//Precondition: Calculates 1-D index using Row and Column
//Postcondition: Returns corresponding index's square reference
 Square&
Board:: sub(const int j, const int k){
    int index = (j-1)*N + (k-1);
    return bd[index];
}
//=================================================
//This is called from the virtual function get PossiblityString
Square&
Board:: sub1(int j, int k) const{
    int index = (j-1)*N + (k-1);
    return bd[index];
}
//=================================================
//Precondition:  Reads the file char by char till end and validates input
//Postcondition: Constructs N*N squares by using subscript function
void
Board:: getpuzzle(){
    char box;
    int count = 0;
    for(;;){
    if(file.eof()) break;
    for(int p=1;p<=N;p++){
        for(int q=1;q<=N;q++){
            if(file >> box){
            if(!validate(box))throw WrongBoardInput();
            sub(p,q) = Square(box, p, q);
            if(q == N) cout <<  "\n";
            count++;
            if(count > N*N) throw ExtraJunkInput();
         }
            else{
                if(count < N*N) throw Badfile();
            }
        }
        cout << "\n";
    }
  }
}
//=====================================================
//Precondition: Prints all N*N squares and N*3 Clusters
//Postcondition: Delegates print function in Square and Cluster Classes
ostream&
Board:: print1(ostream& ofs){
    int k = 1;
    for(int p=0; p<N*N; p++){
        if(p % N == 0)
        cout <<"\n"<< endl;
        bd[p].sqprint(ofs);
    }
    cout << "----------------------------------------------------------" <<endl;
    cout << "\n" << "\n" << "\n";
    cout << "I am printing all clusters that are constructed" << "\n" <<endl;
    
    for(Cluster* cl: clue){
        if(k % 10 == 0){cout<<"\n";}
        k++;
        cl->Clprint(ofs);
    }
    return ofs;
}
//=======================================================
//Precondition: Ensures the starting index of new Row, Column and Box
//PostCondition: Calls each of them N times to make respective Clusters
void
Board::makeClusters(){
    for(int p=1; p<=N; p++){
        createRow(p);
    }
    for(int p=1; p<=N; p++){
        createColumn(p);
    }
}
//=======================================================
//Precondition: Creates row Cluster by assigning N square pointers,
//Provides 2 way access to clusters and squares
//Postcondition: Adds the created clusters to N squares, stores clusters in vector
void
Board::createRow(const short j){
    Square* spTemp[N];
    const char* cType = cltrtype[1];
    for(int k=1; k<=N; k++){
        spTemp[k-1] = &sub(j, k);
    }
    Cluster *c = new Cluster(cType,spTemp, N);
    for(int p=1; p<=N; p++){
        spTemp[p-1]->addCluster(c);
    }
    clue.push_back(c);
}
//========================================================
void
Board::createColumn(const short j){
    Square* spTemp[N];
    const char* cType  = cltrtype[2];
    for(int k=1; k<=N; k++){
        spTemp[k-1] = &sub(k, j);
    }
    Cluster *c = new Cluster(cType,spTemp, N);
    for(int p=1; p<=N; p++){
        spTemp[p-1]->addCluster(c);
    }
    clue.push_back(c);
}
//========================================================
void
Board::createBox(const short j, const short k){
    Square* spTemp[N];
    int p=0;
    const char* cType = cltrtype[0];
    for(int q=0; q<3 ; q++){
        for(int s=0; s<3; s++){
            spTemp[p] = &sub(q+j, s+k);
            p++;
        }
    }
    Cluster *c = new Cluster(cType,spTemp, N);
    for(int p=1; p<=N; p++){
        spTemp[p-1]->addCluster(c);
    }
    clue.push_back(c);
}
//============================================================
void
Board::createSixyHBox(const short j, const short k){
    Square* spTemp[N];
    int p=0;
    const char* cType = cltrtype[0];
    for(int q=0; q<2 ; q++){
        for(int s=0; s<3; s++){
            spTemp[p] = &sub(q+j, s+k);
            p++;
        }
    }
    Cluster *c = new Cluster(cType,spTemp, N);
    for(int p=1; p<=N; p++){
        spTemp[p-1]->addCluster(c);
    }
    clue.push_back(c);
}
//============================================================
void
Board :: createSixyVBox(const short j, const short k){
    Square* spTemp[N];
      int p=0;
      const char* cType = cltrtype[0];
      for(int q=0; q<3 ; q++){
          for(int s=0; s<2; s++){
              spTemp[p] = &sub(q+j, s+k);
              p++;
          }
      }
      Cluster *c = new Cluster(cType,spTemp, N);
      for(int p=1; p<=N; p++){
          spTemp[p-1]->addCluster(c);
      }
      clue.push_back(c);
}
//============================================================
void
Board::createDiagonalOne(){
     Square* spTemp[N];
     const char* cType  = cltrtype[3];
     for(int k=1; k<=N; k++){
            spTemp[k-1] = &sub(k,k);
        }
     Cluster *c = new Cluster(cType,spTemp, N);
    for(int k=1; k<=N; k++){
        spTemp[k-1]->addCluster(c);
    }
     clue.push_back(c);
}
//============================================================
void
Board::createDiagonalTwo(){
     Square* spTemp[N];
     const char* cType  = cltrtype[3];
     for(int p=1,q=N; p<=N || q>=1; p++,q--){
            spTemp[p-1] = &sub(p,q);
        }
    Cluster *c = new Cluster(cType,spTemp, N);
    for(int k=1; k<=N; k++){
        spTemp[k-1]->addCluster(c);
    }
     clue.push_back(c);
}
//============================================================
//A private function to call shooping operation on N*N squares
void
Board::callShoop(){
    for(int p=0; p<N*N; p++){
        bd[p].sqrshoop();
    }
}
//==========================================================
//A private function to Validate each character in the file
const bool
Board:: validate(const char s){
    if(s == '-') return true;
    int value = s - '0';
    if(value > 0 && value < N+1){ return true; }
    return false;
}
//============================================================
//This is called from game class. Allows user to mark on board.
void
Board:: markBoard(){
    int p,q;
    char value;
    cout << "Enter row number: " <<endl;
    cin >> p;
    if(cin.fail()){cin.clear(); cin.ignore(); throw Inputmismatch();}
    if(p<1 || p>N ) throw WrongRowOrColumn();
    cout << "Enter column number: " <<endl;
    cin >> q;
    if(cin.fail()){cin.clear(); cin.ignore(); throw Inputmismatch();}
    if(q<1 || q>N) throw WrongRowOrColumn();
    cout << "Enter value: " <<endl;
    cin >> value;
    if(!validate(value))throw WrongBoardInput();
    sub(p,q).mark(value);
    callShoop();
}
//==============================================================
//PreCondition: Creates N*N State objects
//PostCondition: Initializes all state objects and creates a new frame
Frame* 
Board:: move(){
    State sta[N*N];
    for(int k=1; k<=N*N; k++){
        sta[k-1] = bd[k-1].getstateobj();
    }
    Frame *fr = new Frame(sta, N);
    return fr;
}
//==============================================================
//PreCondition: Creates a new N*N state objects
//PostCondition: Initializes state objects with topmost frame and restores states
//Called from Game with topmost frame on the stack.
void
Board:: restoreState(Frame* f){
    cout << "I am restoring the board" <<endl;
    State *stobj = new State[N*N];
    stobj = f->getFrames();
    for(int p=1; p<=N*N; p++) {bd[p-1].getstateobj() = stobj[p-1];}
}
//===============================================================
//Used to manually turnoff poslist.
void
Board:: Turnoffpolist(){
    int r,p,q;
    cout << "Enter row number: " <<endl;
    cin >> p;
    if(cin.fail()){cin.clear(); cin.ignore(); throw Inputmismatch();}
    if(p<1 || p>N) throw WrongRowOrColumn();
    cout << "Enter column number: " <<endl;
    cin >> q;
    if(cin.fail()){cin.clear(); cin.ignore(); throw Inputmismatch();}
    if(q<1 || q>N) throw WrongRowOrColumn();
    cout << "Enter the value to turn off" <<endl;
    cin >> r;
    sub(p, q).turnOff(r);
}
//==================================================================
void
Board:: printFrame(Frame* f){
     State* stobj = f->getFrames();
    for(int q=1; q<=N*N; q++){
        cout << stobj[q-1] << endl;
    }
}
//===================================================================
//To create box clusters for traditional board
void
TradBoard :: createboxclusters(){
    //This is for creating traditiona box cluster
    for (int t = 1; t <= N; t+=3) {
        for (int j = 1; j <= N; j+=3) {
           createBox(t,j);
        }
    }
}
//====================================================================
//To create all diagonal clusters
void
DiagBoard :: creatediagaonalclusters(){
    createDiagonalOne();
    createDiagonalTwo();
}
//====================================================================
//To create box cluster for sixy board
void
SixyBoard :: createHboxcluster(){
    for (int t = 1; t <= N; t+=2) {
           for (int j = 1; j <= N; j+=3) {
               createSixyHBox(t,j);
           }
       }
}
//======================================================================
void
SixyBoard :: createVboxcluster(){
    for (int t = 1; t <= N; t+=3) {
           for (int j = 1; j <= N; j+=2) {
               createSixyVBox(t,j);
           }
    }
}
//================================================================================
Board:: ~Board(){
delete [] bd;
for(Cluster* cl : clue){
    delete cl;
}
}
