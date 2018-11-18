#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "queue.h"
#include "stack.h"
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"

using namespace std;

void loadDictionary(Lexicon& dictionary);
void getWords(string& wordA, string& wordB);
void generate(string& firstWord, string& secondWord, Lexicon& dictionary);
void getLadder(string& firstWord, string& secondWord, Lexicon& dictionary);
bool isNeighbour(string lastWord, string newWord);

int main() {

    Lexicon dictionary;
    string word1 = "";
    string word2 = "";

    loadDictionary(dictionary);                                            //need to add validation of file, words and create a cycle
    getWords(word1, word2);
    getLadder(word1, word2, dictionary);
 // showResults();                                                         //add function to show the shortest path in the opposite way

    cout << "Have a nice day motherfucker." << endl;
    return 0;
}
//*****************creates the new dictionary acording to the directory************************************************

void loadDictionary(Lexicon& dictionary){
    ifstream stream;
    string directory = getLine("Please enter the filename: ");                                         //we store the name of the file in Fname st
       stream.open(directory);                                                                         //we open the file **adjustment needed --> loop nd file verification

        string buffer = "";
           while(stream >> buffer){
                    dictionary.add(buffer);
                       }
       stream.close();
   //    cout << dictionary;
}

//**********************************this function gets the two words from the ladder************************************

void getWords(string& wordA, string& wordB){

     wordA = getLine("Please enter the first word: ");
     wordA = toLowerCase(wordA);

     wordB = getLine("Please enter the second word: ");
     wordB = toLowerCase(wordB);
}


//*********************************ladder generator**********************************************************************

void getLadder(string& firstWord, string& secondWord, Lexicon& dictionary){
    generate(firstWord, secondWord, dictionary);
 //   compare(firstWord, secondWord);
 //   allocateWords();
}

//**************************************+this function prints all the values of the ladder through the stack***************

void showResults(Stack<string>& stack){
    while(!stack.isEmpty()){              // while there are words inside the stack, pop them out
      cout << stack.pop();
    }
}

//**************+********************* brute force path generator*******************************************************************************

void generate(string& firstWord, string& secondWord, Lexicon& dictionary){
 Queue<Stack<string>> stackQueue;               //we create the queue of stacks to store all posible paths
 Stack<string> stack;                           //string stack to store the words
 stack.push(firstWord);                         //we load the first word by the user in the stack

    stackQueue.enqueue(stack);                  //we put the stack in the queue to be processed
  //  string currentWord = "";
    Lexicon wordCollection;                     //lexicon to store all proccesed words in a set

    while(!stackQueue.isEmpty()){               //while the queue has something to process
      Stack<string> stackWord = stackQueue.dequeue();    //we take it out of the queue
       string temporaryWord = stackWord.peek();          //take a peek to not to modify the contents

        if(temporaryWord == secondWord){cout << stackWord;}  //if the last word in the stack is the second word -> we have found the path

             for(unsigned int index = 0; index < firstWord.length(); index++){          //here we generate all possible words with a serial generator
                for(char letter = 'a'; letter < 'z'; letter++){                         //we vary according the index and explore every possibility with the alphabet

                             string partOne = temporaryWord.substr(0, index);           //we pick the firest unmodified part of the string
                             char partTwo = letter;                                     //the variable char
                             string partThree = temporaryWord.substr(index + 1);        //the last unmodified part
                             string theWord =  partOne + partTwo + partThree;           //full word

                                if(dictionary.contains(theWord) && isNeighbour(temporaryWord, theWord) && !wordCollection.contains(theWord))  //if it's a valid word, neighbour of the last word on the stack, and it's not been processed yet, we addit to the current stack                                           //if the generated word is valid and is different from the original word
                                             {wordCollection.add(theWord);
                                             Stack<string> newStackWord = stackWord;    //we create a new stack, and just add it to the queue as a new path to be processed
                                            newStackWord.push(theWord);                 //add it to the stack
                                            stackQueue.enqueue(newStackWord);
                                            // cout << stackWord << " stack lenght: " << stackWord.size(); ***************debug***************
                                            //   cout <<  " stackQueue size: " <<  stackQueue.size() << stackQueue << endl;



                                                                                                    }

        }
    }
}

}

//****************************************determines if a word is a neighbour or not, if it has just one different letter it classifies**********++
bool isNeighbour(string lastWord, string newWord){
   unsigned int letterCount = 0;                                           //event counter
   for(unsigned int i = 0; i < lastWord.length(); i++){
        char lastWordLetter = lastWord[i];
        char newWordLetter = newWord[i];

             if(lastWordLetter == newWordLetter){++letterCount;}           //if every character is the same in the same location, we add ++
   }

        if(letterCount == lastWord.length() - 1 && lastWord != newWord){   //if it's number of events is exactly the index minus one it classifies, else it´s the same word
             return true;
    }
                else{
                    return false;                                          //else it´s not neighbour
    }
}
