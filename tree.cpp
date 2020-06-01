#include <iostream>
#include <fstream>
#include "tree.h"
using namespace std;

//Default Constructor: Setting everything to NULL
template<class T>
tree<T>::tree(){ 
  root = NULL;
  totalNumWords = 0;
  uniqueWords = 0;  
  uniqueWords3 = 0;
  avgWordLength = 0;
  totWordLength = 0;
	aveSentenceLength = 0;
}



//Creates a new node
template<class T>
node<T>* tree<T>::createLeaf(string info){
  node<T>* n = new node<T>;
  n->info = info;
  n->left = NULL;
  n->right = NULL;
  n->nodeCount = 1;
  return n;
}



//Deconstrcutor: Destroys all the data using the removeSubTree function
template<class T>
tree<T>::~tree(){
  removeSubTree(root);
}



//Flexible remove function for the tree which removes all the nodes underneeth 
template<class T>
void tree<T>::removeSubTree(node<T> *givenRoot){
  if(givenRoot != NULL){
    if(givenRoot->left != NULL){
      removeSubTree(givenRoot->left);
    }
    else if(givenRoot->right != NULL){
      removeSubTree(givenRoot->right);
    }
    else delete givenRoot;
  }
}



//Calculates the average number of words in the paragraph
template<class T>
void tree<T>::avgWord(){
    avgWordLength = totWordLength / totalNumWords;
}

//Converts all charecters in the string to upper case
template<class T>
void tree<T>::stringToUpper(string& x){
  for(int i = 0; i < x.size(); i++){
    x[i] = toupper(x[i]);
  }
}




//Recursive add to tree function to automatically keep adding all the nodes
template<class T>
void tree<T>::addToTreePrivate(string WORD, node<T>* ptr){
  
  //accounting for null
  if (WORD < ptr->info){
    if(ptr->left != NULL){
      addToTreePrivate(WORD, ptr->left);
    }
    else {
      //creating node on left side if empty
      ptr->left = createLeaf(WORD);
    }
  }
  //going down the tree on both left and right side recursively
  else if (WORD > ptr->info){
    if(ptr->right != NULL){
      addToTreePrivate(WORD, ptr->right);
    }
    else {
      ptr->right = createLeaf(WORD);
    }
  }
  //adding to the counters if there are recurring words in the paragraph
  else if (WORD == ptr->info){
    uniqueWords += 1;
    ptr->nodeCount += 1;
    if (WORD.length() > 3){
      uniqueWords3 += 1;
    }
  }
}




//Main add to tree function that is used to go through all the processes asked
template<class T>
void tree<T>::addToTree(string WORD){

  //making everything uppercase to ingore same words being repeated in the tree
  stringToUpper(WORD);

  //counting all the words as they are being added to the tree
  totalNumWords += 1;
  totWordLength += WORD.length();

  //making the tree recursive for simple implementation
  if(root != NULL) {
		addToTreePrivate(WORD, root);
	} else
		root = createLeaf(WORD);

}




//Get function to get info from the main
template<class T>
void tree<T>::setAvgSentenceLength(int x) {
  aveSentenceLength = x;
}




//Gets all the unique words with more than 3 letters into a string recursively
template<class T>
void tree<T>::privateGet3LetterWords(string &allWords, node<T>* tempNode) {
  //Taking the 5% rule given in the promt into account
  int x = 0.05 * totalNumWords;

  if(tempNode == NULL){
    return;
  }
  privateGet3LetterWords(allWords, tempNode->left);
  if(tempNode->nodeCount > x && tempNode->info.size() > 3  ){
    
    allWords += tempNode->info; allWords += "\n" ;
  } 
  privateGet3LetterWords(allWords, tempNode->right);
}
//Getting all unique 3 letter words that appear more than 5% of the time
template<class T>
string tree<T>::get3LetterWords(){
  string allWords = "";
  node<T> *tempNode = new node<T>;
  tempNode = root;
  privateGet3LetterWords(allWords, tempNode);
  return allWords;
}





//Gets all the unique words(that have a nodeCount of more than 1)
template<class T>
void tree<T>::privategetUniqueWords(string &allWords, node<T>* tempNode) {
 if(tempNode == NULL){
   return;
 }  
  privategetUniqueWords(allWords, tempNode->left);
  if(tempNode->nodeCount > 1){
    allWords += tempNode->info; allWords += " ";
  } 
  privategetUniqueWords(allWords, tempNode->right);
}
//Main function to get uniqueWords
template<class T>
string tree<T>::getUniqueWords(){
  string allWords = "";
  node<T> *tempNode = new node<T>;
  tempNode = root;
  privategetUniqueWords(allWords, tempNode);
  return allWords;
}




//Prints all the data calculated and all the infomation inside the tree into a text file
template<class T>
void tree<T>::printToFile() {
  
  //Final calculation to get average number of words
  avgWord();

  //initializing output object;
  ofstream rF("Analysis.txt");

  //Setting the struction of how the texts should be written

  rF << "File Name: Analysis.txt\n\n";
  
  rF << "\t\t\t Statistical Summary\n";
  rF << "\t\t\t---------------------\n\n";
  
  rF << "TOTAL NUMBER OF WORDS: " << totalNumWords << "\n";
  rF << "TOTAL NUMBER OF 'UNIQUE' WORDS: " << uniqueWords << "\n";
  rF << "TOTAL NUMBER OF 'UNIQUE' WORDS MORE THAN THREE LETTERS: " << uniqueWords3 << "\n";
  rF << "AVERAGE WORD LENGTH: " << avgWordLength << " charecters\n";
  rF << "AVERAGE SENTENCE LENGTH: " << aveSentenceLength << " words\n\n";

  rF << "\t\t\t STYLE WARNINGS\n";
  rF << "\t\t\t----------------\n\n";

  rF << "WORDS USED TOO OFTEN(0 if nothing posted): \n\n";
  string list_1= get3LetterWords(); 
  list_1 += " ";

  int index = 1;
  string pass = "";
  for (int i = 0; i < list_1.size(); i++){
    if(list_1[i] == ' '){
      rF << index << ") ";
      rF << pass << endl;
      pass = "";
      index ++;
    }
    else {
      pass += list_1[i];
    }
  }

  //Style WARNINGS
  if(aveSentenceLength > 10){
    rF << "AVERAGE SENTENCE LENGTH TOO LONG: " << aveSentenceLength << endl;
  }
  if(avgWordLength > 5) {
    rF << "AVERAGE WORD LENGTH TOO LONG: " << avgWordLength << endl;
  }

  rF << "\n\n\t\t\t\t Index of Unique Words" << endl;
  rF <<     "\t\t\t\t-----------------------\n\n"; 
  

  //Makes an index and prints everything out nicely
  string list_2 = getUniqueWords(); 
  char x = 'A';
  pass = "";
  rF << " " << x << "\n---" << endl;

  for (int i = 0; i < list_2.size(); i++){
    if (list_2[i] == ' '){
      rF << pass << endl;
      if (list_2[i+1] == x){
      }
      else {
        if(i < list_2.size()){
          x++;
          rF << endl << " " << x << "\n---" << endl;
        }
      }
      pass = "";
    }
    else {
      pass += list_2[i];
      
    }

  }

  rF.close();



}