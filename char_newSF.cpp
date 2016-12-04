//
// Created by user on 01.12.2016.
//
#include <string>
using namespace std;
/*
 * Define SymbolCode Class
 */
class SymbolCode {
private:
     char sym;
     int freq;
     string cd;
public:
     SymbolCode( char in_symbol, int in_frequency );
     char getSym(void);
     int getFreq(void);
     string getCd(void);
     void addCd(string in_code);
};


/*
 * End SymbolCode Class
 */