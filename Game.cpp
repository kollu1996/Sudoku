//
//  Game.cpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 9/17/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#include "Game.hpp"
//==================================================================
//Pre Condition: Opens a file name with parameter as value
//Post Condition: Checks if file is opened successfully or not and validates
//game type and passes the control to appropriate board. Shows the Board UI.
Game:: Game(const string filename){
    fobj.open(filename);
        if(!fobj.is_open())throw WrongFilname();
        fobj >> gameType;
        if(fobj.eof()) {
            cout << "I reached end of file" <<endl; throw BlankFile();
        }
        if(gameType == 't' || gameType == 'd') gameSize = 9;
        else gameSize = 6;
        string valid = "tTdDsS";
        if(valid.find_first_of(gameType) == string::npos){
        throw WrongGameType(gameType);
        }
    if(gameType == 't') b = new TradBoard(gameSize, fobj);
    else if (gameType == 'd') b = new DiagBoard(gameSize,fobj);
    else b = new SixyBoard(gameSize, fobj);
    Viewer v1(gameSize, gameSize, *b);
    v1.show(cout);
    fobj.close();
   }
//===================================================================
//Pre Condition: Passes all required arguments for menu_c function on line 49
//Post Condition: Gets a perfectly validated menu option as return statement
//from menu function.
//m for Mark, u for Undo, r for Redo
//s for Save, e for Restore , t for Turnoff
//p for Print, q for Quit
void Game::run(){
    char choice;
    const char* title = "SUDOKU GAME";
    string valid = "MmUuRrSsEeQqTtPp";
    Undo_Stack.push(b->move());
    for(;;){
        choice = menu_c(title,8,menu,valid);
        choice = tolower(choice);
        switch(choice){
            case 'm':{
                try{
                b->markBoard();
                Undo_Stack.push(b->move()); //b->move will return a new frame object
                Redo_Stack.zap();
                }
                catch(WrongRowOrColumn& W ){
                    W.print();
                    continue;
                }
                break;
            }
            case 'u':{
                try{
                if(Undo_Stack.size() <= 1) throw Emptystack();
                Frame* f = Undo_Stack.stack_top();
                Undo_Stack.pop();
                Frame *g = Undo_Stack.stack_top();
                Redo_Stack.push(f);
                b->restoreState(g);
                }
                catch(Emptystack& e){
                    e.print();
                    continue;
                }
                break;
            }
            case 'r':{
                if(Redo_Stack.size()==0) return;
                Frame *f = Redo_Stack.stack_top();
                Redo_Stack.pop();
                Undo_Stack.push(f);
                b->restoreState(f);
                break;
            }
            case 't': {
                b->Turnoffpolist();
                Undo_Stack.push(b->move());
                Redo_Stack.zap();
                break;
            }
            case 's': {
                Frame* f = Undo_Stack.stack_top();
                makefile();
                f->serialize(file);
                file.close();
                break;
            }
            case 'e':{
                openfile();
                Undo_Stack.zap();
                Redo_Stack.zap();
                Frame *f = new Frame();
                f->realize(fil);
                Undo_Stack.push(f);
                b->restoreState(f);
                Undo_Stack.pop();
                fil.close();
                break;
            }
            case 'p':{
                testBoard();
                break;
            }
        }
        if(choice == 'q') return;
        else if(choice != 'p'){
            Viewer v1(gameSize, gameSize, *b);
            v1.show(cout);
        }
    }
}
//=======================================================================
//This prints all all squares and clusters constructed.Choose option p for this
void
Game:: testBoard(){
            cout << "\n" << "Printing Board" <<endl;
            b->print1(cout);
}
//=======================================================================
void
Game:: makefile(){
    cout << "Enter a file name: " <<endl;
    cin >> filename;
    file.open(filename, ios::binary);
    if(!file) WrongFilname();
}
//========================================================================
void
Game:: openfile(){
    cout << "Enter a file name: " <<endl;
    cin >> filename;
    fil.open(filename, ios::binary);
    if(!fil) throw WrongFilname();
    if(fil.eof()) throw BlankFile();
    if(!fil.good()) throw WrongFilname();
}

