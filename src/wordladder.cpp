#include <cctype>
#include <cmath>,
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "queue.h";
#include "stack.h";
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"

using namespace std;

void loadDictionary(Lexicon& dictionary);
void getWords(string& wordA, string& wordB);
void generate(string& firstWord, string& secondWord, Lexicon& dictionary);
void getLadder(string& firstWord, string& secondWord, Lexicon& dictionary);

int main() {
    Queue<Stack<string >> stackQueue;
    Lexicon dictionary;
    string word1 = "";
    string word2 = "";

    loadDictionary(dictionary);

    getWords(word1, word2);



    getLadder(word1, word2, dictionary);
 //   showResults();


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

     wordB =  getLine("Please enter the second word: ");

}




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

//**************+

void generate(string& firstWord, string& secondWord, Lexicon& dictionary){

    vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; // vector with the letters to generate words
    unsigned int alphabetSize = alphabet.size();

    for(unsigned int index = 0; index < firstWord.length(); index++){

        for(unsigned int letter = 0; letter < alphabetSize; letter++){
                             string partOne = firstWord.substr(0, index);
                             char partTwo = alphabet.at(letter);
                             string partThree = firstWord.substr(index + 1);
                             string wordOne =  partOne + partTwo + partThree;

                                if(dictionary.contains(wordOne) && wordOne != firstWord)                                             //if the generated word is valid and is different from the original word
                                              {                                                                                      //add it to the stack
                                                    cout << " word found!: " << wordOne << endl;
                                                                                                    }
        }
    }

}
