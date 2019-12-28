//
//  Cluster.hpp
//  P1-Sreenikhil
//
//  Created by Sreenikhil Kollu on 10/1/19.
//  Copyright © 2019 Sreenikhil Kollu. All rights reserved.
//

#ifndef Cluster_hpp
#define Cluster_hpp

#include "tools.hpp"
#include "State.hpp"
class Cluster{
    int N;
    const char* cltrname;
    Square** a;
public:
    ~Cluster() {delete []a;}
     Cluster(const char* Ctype , Square** b, int size ){
        cltrname = Ctype;
        this->N = size;
        a = new Square*[size];
        for(int m=1; m<=size; m++){
            a[m-1] = b[m-1];                 //Initializes all N square pointers
        }
    }
    void shoopcltr(char c);
    ostream& Clprint(ostream& ofs);
};
inline ostream& operator<<(ostream& cl, Cluster*& c){return c->Clprint(cl);}
#endif /* Cluster_hpp */
