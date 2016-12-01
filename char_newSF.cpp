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
     char symbol;
     int frequency;
     string code;
public:
     SymbolCode( char in_symbol, int in_frequency );
     char getSymbol( void );
     int getFrequency( void );
     string getCode( void );
     void addCode( string in_code );
};


/*
 * End SymbolCode Class
 */