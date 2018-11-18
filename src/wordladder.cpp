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

    loadDictionary(dictionary);
    getWords(word1, word2);
    getLadder(word1, word2, dictionary);
 // showResults();

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
 Queue<Stack<string>> stackQueue;
 Stack<string> stack;
 stack.push(firstWord);

 stackQueue.enqueue(stack);
 string currentWord = "";
Lexicon wordCollection;

while(!stackQueue.isEmpty()){
    Stack<string> stackWord = stackQueue.dequeue();
    string temporaryWord = stackWord.peek();


    if(temporaryWord == secondWord){cout << stackWord;}


     for(unsigned int index = 0; index < firstWord.length(); index++){
            for(char letter = 'a'; letter < 'z'; letter++){


                             string partOne = temporaryWord.substr(0, index);
                             char partTwo = letter;
                             string partThree = temporaryWord.substr(index + 1);
                             string theWord =  partOne + partTwo + partThree;
                            // cout << " debug " << theWord << "  " << temporaryWord << endl;





                                if(dictionary.contains(theWord) && isNeighbour(temporaryWord, theWord) && !wordCollection.contains(theWord))                                             //if the generated word is valid and is different from the original word
                                             {wordCollection.add(theWord);

                                             Stack<string> newStackWord = stackWord;
                                            newStackWord.push(theWord);//add it to the stack
                                            stackQueue.enqueue(newStackWord);
                                             // cout << stackWord << " stack lenght: " << stackWord.size();
                                           //   cout <<  " stackQueue size: " <<  stackQueue.size() << stackQueue << endl;



                                                                                                    }

        }
    }
}


}


bool isNeighbour(string lastWord, string newWord){
   unsigned int letterCount = 0;
   for(unsigned int i = 0; i < lastWord.length(); i++){
        char lastWordLetter = lastWord[i];
        char newWordLetter = newWord[i];

             if(lastWordLetter == newWordLetter){++letterCount;}
   }
//cout << "letterCount" << letterCount << endl;
    if(letterCount == lastWord.length() - 1 && lastWord != newWord){
        return true;
    }
    else{
        return false;
    }
}
