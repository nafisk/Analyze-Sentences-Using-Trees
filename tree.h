//Tree class to add, analysize and print all the information required by the promt
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include "node.h"
using namespace std;

template<class T>
class tree{
    private:
      node<T> *root;
      int totalNumWords;                                                //Total Number of Words
      int uniqueWords;                                                  //Number of Unique Words
      int uniqueWords3;                                                 //Numbers of Unique Words more than 3 lettr
      int avgWordLength;                                                //Average Length of all the words
      int totWordLength;                                                //Total Count of all word lenghts
      int aveSentenceLength;                                            //Average Sentence Length of the entire paragraph
      void addToTreePrivate(string WORD, node<T>* ptr);                 //Recursive function for adding nodes to tree
      void privateGet3LetterWords(string &allWords, node<T>* tempNode); //Recursive function to get uniqueWords > 3 letters
      void privategetUniqueWords(string &allWords, node<T>* tempNode);  //Recursive function to get all uniqueWords

    public:
      tree();                                                           //constructor
      ~tree();                                                          //deconstructor
      node<T>* createLeaf(string info);                                 //Initializes and creates a new node
      void removeSubTree(node<T> *givenRoot);                           //Removes all children from root given
      void addToTree(string WORD);                                      //Main function to add nodes to tree
      void avgWord();                                                   //Calculates avg number of words after adding all nodes
      void setAvgSentenceLength(int);                                   //Gets setAvgSentenceLength from the main
      void printToFile();                                               //Prints all the info into an analysis document
      string get3LetterWords();                                         //String to hold all the uniqueWords over 3 letter
      string getUniqueWords();                                          //String to hold all the uniqueWords
      void stringToUpper(string& x);                                    //Converts charecters in the string to uppercase


};
#endif