//
// Created by user on 11.12.2016.
//
#include "node_for_rb.cpp"

class RB_tree{

    //field for root
    nd_rb *root;
    nd_rb *q;

public :
    //constructor
    RB_tree(){
        root = nullptr;
        q = nullptr;
    }

    void Create();
    void Delete();
    void del(nd_rb *);
    void remove(int k);
    void delfix(nd_rb *child);
};
