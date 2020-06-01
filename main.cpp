#include <iostream>
#include <fstream>
#include <cstdlib>
#include "tree.cpp"
#include <string>
using namespace std;



int main() {

 //opening and reading the file data 
 ifstream myFile;
 string sentence;
 myFile.open("file.txt");

 //Tree class object initialization
 tree <string> analyse;

  //File validation
  if(!myFile.is_open()){
  cout << "Error. Cannot Open File" << endl;
  exit(0);
  }

  //sentence length variables
  int aveSentenceLength, wordsInSentence = 0;

  //counter for sentences
  int count = 1;

  string WORD; 

  /* 
    Each line is seperately taken out by getline and is then send to the tree words by words.
  */
  while( getline(myFile, sentence, '.') ) {
    count += 1; //counting sentences
    for(int i = 0; i < sentence.length(); i++){

    //helps ignore spaces and accounts to remove commas
    if ( sentence[i] == ' ' || sentence[i]== ','){
      if ( sentence[i+1] == ' '){
        continue;
      }
      else {
        wordsInSentence += 1;
        //sending one word at a time to be place inside the tree
        analyse.addToTree(WORD);
        WORD = "";
      }
    }
    else {
      //adding each charecter to the word string
      WORD += sentence[i];
      }
    }

  }

  //calculates the avg sentence length and sends it to the class
  aveSentenceLength = wordsInSentence / count;
  analyse.setAvgSentenceLength(aveSentenceLength);

  //Prints out the data in the tree to the analysis.txt file
  analyse.printToFile();

  myFile.close();

  cout << "\t\t\t\tWelcome to the Tree Project" << endl;
  cout << "\t\t\t\t---------------------------\n";
  cout << "\t\t\t\t\t\tBy Nafis Khan\n";
  cout << "\t\t\t\t\t\t-------------\n\n";
  cout << "All the text data placed inside the text file has been analized.\nPlease check analysis file.\n";
  cout << "\n\nEnding Program";
  exit(0);


  return 0;
}