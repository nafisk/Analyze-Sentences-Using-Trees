//Node class for the tree
#ifndef TREE_H
#define TREE_H
#include <iostream>
using namespace std;

template <class T>
class node{
    public:
    
    //Each node contains a pointer to left and right node
    //It also contains the word and how many times the words exists in the file
    node<T> *left;
    node<T> *right;
    string info;
    int nodeCount;
};
#endif
