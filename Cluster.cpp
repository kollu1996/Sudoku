//
//  Cluster.cpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 10/1/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//
#include "Cluster.hpp"

//Delegates to square print function to print all the clusters
ostream&
Cluster::Clprint(ostream& ofs){
    ofs << cltrname << "Cluster" << " " <<endl;
    for(int i=1; i<=N; i++){
        a[i-1]->sqprint(ofs);
    }
    return ofs;
}
//====================================================
//Precondition: To remove a specified value from all squares in that cluster
//Postcondition: Delegates turnOff function in square to remove.
void
Cluster:: shoopcltr(char c){
    int v = c - '0';
    if(v > 0){
        for(int q = 1; q<=N; q++){
            a[q-1]->turnOff(v);
        }
    }
}

