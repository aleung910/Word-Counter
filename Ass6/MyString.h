#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int COLUMN_WIDTH = 60;
bool isAcceptable(char c, bool isFirstChar, bool isNumber) {
    return ((isNumber && c == ',') || ((c >= 48) && (c <= 57)) || ((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)) || (c == '-') || (c == '\'') || (c == '`' && !isFirstChar));
}




class MyString {
private:
    string str; //a phrase may contain one to five words
    int frequency;
public:
    MyString(std::string s)
    {
        str = s;
        frequency = 1;
    }

    // Accessor function for string
    string getStr() const
    {
        return str;
    }

    int getFrequency() const {
        return frequency;
    }

    bool operator==(const MyString& rhs) const // used in linear search
    {
        return (str == rhs.str);
    }

    bool operator >(MyString s) const // used in sort algorithm
    {
        if (frequency == s.frequency)
        {
            return (s.str > str);
        }
        return (frequency > s.frequency);
    }

    bool operator <(MyString s) const // used in sort algorithm
    {
        if (frequency == s.frequency)
        {
            return (s.str < str);
        }
        return (frequency < s.frequency);
    }

    MyString operator ++(int)  // used to increment the frequency
    {
        //Postfix 
        MyString temp(*this);
        frequency++;
        return temp; //return temp?
    }


    friend ofstream& operator<<(ofstream& o, const MyString& obj);


};

ofstream& operator<<(ofstream& o, const MyString& obj) // output to file
{

    o << left << setw(COLUMN_WIDTH) << obj.str << left << (obj.frequency) << endl;


    return o;
}



#endif
