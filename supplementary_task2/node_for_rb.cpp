//
// Created by user on 11.12.2016.
//
struct nd_rb{

    // color of the node(false for red, true for black)
    bool color;
    int key;

    nd_rb *parent;
    nd_rb *left;
    nd_rb *right;

    nd_rb(int KEY){
        key = KEY;
        color = false;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    };
};

