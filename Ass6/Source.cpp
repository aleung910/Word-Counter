//https://www.geeksforgeeks.org/vectorpush_back-vectorpop_back-c-stl/
//USING PUSH BACK AND PUSH BACK
//https://www.youtube.com/watch?v=FK9YDChyrDc&t=65s&ab_channel=SlackertoHacker
//for vector sort
//https://cplusplus.com/reference/algorithm/sort/
//using sort(x.begin(), x.end())
//chatgpt to undesrtand overloading better for the program. needed help in putting punctation for D.C vs DC.
//removing the trailing puntuations form teh words i had to use ispunct
//https://cplusplus.com/reference/cctype/ispunct/
//https://cplusplus.com/reference/algorithm/find/
// find is searching for  MyString object that has the same string value as phrase. 

//question our professor said if the number on the top is slightly off its fine in class. Will that apply here since his code doesnt read all the words? 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "MyString.h"
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int adjacent;
    string infilename, outfilename;

    //getting data from user
    cout << "Enter the source data file name: ";
    cin >> infilename;

    cout << "How many Adjacenent words in a phrase, enter 1-5: ";
    cin >> adjacent;

    cout << "Enter the phrase frequency file name: ";
    cin >> outfilename;

    ifstream infile;
    infile.open(infilename); //reading input

    int numWord = 0;
    int numPhrases = 0;
    string word;
    vector<MyString> words;
    vector<MyString> addingwords;


    while (infile >> word)
    {
        string CAPS;
        bool isFirstChar = true;
        bool isNumber = false;


        for (char c : word) {
            if (isAcceptable(c, isFirstChar, isNumber)) {
                CAPS += toupper(c);
                isFirstChar = false;
                if (c >= 48 && c <= 57) { //if number i add comma
                    isNumber = true;
                }
            }
        }


        if (CAPS.empty()) {
            continue; // Skip word if it is not acceptable
        }


        while (CAPS.size() > 0 && ispunct(CAPS.back()) && CAPS.back() != '-' && CAPS.back() != '\'')
        {
            if (CAPS.size() >= 3 && CAPS.substr(CAPS.size() - 3) == "D.C") // check if the last 3 letters are D.C 
            {
                if (CAPS.size() >= 4 && CAPS[CAPS.size() - 4] == '.') //if the word D.C. has the last period break it off 
                {
                    break; // keep the period before "D.C."
                }
            }
            else if (CAPS.back() == '.')   // remove  other trailing periods
            {
                CAPS.pop_back();
                continue;
            }
            CAPS.pop_back(); //other periods removed
        }

        if (CAPS.size() > 0)
        {

            addingwords.push_back(MyString(CAPS)); //adds mystring object to the new vector
            if (addingwords.size() >= adjacent) // check if we have enough words to form a phrase
            {
                string phrase;
                for (int i = addingwords.size() - adjacent; i < addingwords.size(); i++) {
                    phrase += addingwords[i].getStr() + " ";
                }

                // check if phrase is already in the vector
                auto foundPhrase = find(words.begin(), words.end(), MyString(phrase));

                if (foundPhrase != words.end())
                {
                    foundPhrase->operator++(0); //If mystring has same as phrasefound, pointer to that object. Than returned to be the foundphrase
                    //incrasing the frequency in the op++ in header
                }
                else
                {
                    words.push_back(MyString(phrase));
                    numPhrases++; //incrementing phrase
                }

                // remove first word in the phrase for next loop
                addingwords.erase(addingwords.begin());
            }
            numWord++;
        }
    }

    sort(words.begin(), words.end(), greater<MyString>());


    infile.close();


    ofstream outFile;
    outFile.open(outfilename);

    outFile << "The file: " << infilename << " contains " << numWord << " words, and " << numPhrases << " phrases." << endl;


    for (const auto& word : words)
    {
        outFile << word;
    }
    outFile.close();

    return 0;


}