//
//  main.cpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 9/17/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//


#include "tools.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Board.hpp"
void testSquare();
void rerun(char* c);
using namespace std;
int main(int argc, char* argv[]){
     banner();
     string k;                                                      //File name
     bool flag = true;
     int iteration=0;
    //Sets flag to false if Game logic exception occurs.
     for(;;){
        try{
            //Asks for console input in second iteration rather than command line
            if(iteration >= 1){
                cout << "Enter a file name: " <<endl;
                cin >> k;
                flag = true;
                Game g(k);
                g.run();
                bye();
                if(flag) break;
            }
            
            if(argc < 2) throw NoFilgiven();
            
            Game g(argv[1]);
            g.run();
            bye();
        }
        catch(StreamError& s){
            s.print();
            cout << "Abnormal termination" <<endl;
        }
        catch(GameError& g){
            flag = false;
            g.print();
        }
        catch(...){
            flag = false;
            cout << "You have an exception or error in your code" <<endl;
        }
        if(flag) break;
        iteration++;
    }
}
