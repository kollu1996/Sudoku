//
//  Game.hpp
//  P1-Sreenikhil
//  Created by Sreenikhil Kollu on 9/17/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
#ifndef Game_hpp
#define Game_hpp

#include "tools.hpp"
#include "Board.hpp"
#include "StreamError.hpp"
#include "GameError.hpp"
#include "Viewer.hpp"
class Frame;
class MyStack;
class Game{
    const char* menu[8]=
    {"Mark", "Undo", "Redo", "Save", "Restore", "Turn off", "Print", "Quit"};
    short int gameSize;
    Board *b;
    char gameType;
    ifstream fobj;
    string filename;
    ofstream file;
    ifstream fil;
    MyStack Undo_Stack, Redo_Stack;
public:
    Game(const string filename);
    ~Game() {delete b;}
    void run();
    void testBoard();
    void makefile();
    void openfile();
};
#endif /* Game_hpp */
