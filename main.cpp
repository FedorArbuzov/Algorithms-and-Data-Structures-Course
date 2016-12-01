#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <vector> // подключаем модель Векторов
#include <algorithm>
#include "char_new.cpp"
#include "char_newSF.cpp"
using namespace std;


SymbolCode::SymbolCode( char in_symbol, int in_frequency ) {
    symbol = in_symbol;
    frequency = in_frequency;
    code = "";
}

char SymbolCode::getSymbol( void ) {
    return symbol;
}

int SymbolCode::getFrequency( void ) {
    return frequency;
}

string SymbolCode::getCode( void ) {
    return code;
}

void SymbolCode::addCode( string in_code ) {
    code += in_code;
}


struct MyCompare
{
    bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};

vector<bool> code;
map<char,vector<bool> > table;

void printSymbolCode( SymbolCode in_symbol ) {
     cout << "Symbol: " << in_symbol.getSymbol();
     cout << " Freq: " << in_symbol.getFrequency();
     cout << " Code: " << in_symbol.getCode() << endl;
}

// вектор символов для алгоритма Шенона-Фано
vector<SymbolCode> symbol;

void BuildTable(Node *root)
{
    if (root->left!=nullptr)
    { code.push_back(0);
        BuildTable(root->left);}

    if (root->right!=nullptr)
    { code.push_back(1);
        BuildTable(root->right);}

    if (root->left==nullptr && root->right==nullptr) table[root->c]=code;

    code.pop_back();
}
int str2int(string s)
{
    int n = 0;
    for(int i = s.length(); i > 0; i--)
    {
        n = int(s[i])*i;
    }
    return n;
}

void archivingHof(string path){

    //получение доступа к файлу
    path += ".txt";
    ifstream f(path, ios::in);

    map<char,int> m;


    //чтение из файла
    char c;
    int i = 0;
    while (f >> noskipws >> c) {
        if(i > 2) {
            m[c]++;
            cout << c;
        }
        i++;
    }

    std::list<Node*> t;
    for( map<char,int>::iterator itr=m.begin(); itr!=m.end(); ++itr)
    {
        Node *p = new Node;
        p->c = itr->first;
        p->a = itr->second;
        t.push_back(p);
    }

    while (t.size()!=1)
    {
        t.sort(MyCompare());

        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front();
        t.pop_front();

        Node *parent = new Node(SonL,SonR);
        t.push_back(parent);

    }

    Node *root = t.front();
    BuildTable(root);
    f.clear(); f.seekg(0);

    ofstream g("output.haff", ios::out | ios::binary);
    g<< table.size();
    cout<<table.size();
    for(map<char, vector<bool> >::iterator itr=table.begin(); itr != table.end(); ++itr){
        g<< itr->first;
        cout<< itr->first<<endl;
        vector<bool> x = table[itr->first];
        char buf = 0;
        for(int n=0; n<x.size(); n++)
        {
            buf = buf | x[n];

        }
        g<< buf;
        cout<<buf;
    }
    //запись в файл
    int count=0; char buf=0;
    // проходимся по файлу f
    while (!f.eof())
        //берем каждый символ из f
    { char c = f.get();
        vector<bool> x = table[c];
        for(int n=0; n<x.size(); n++)
            // записываем биты в char
        {buf = buf | x[n]<<(7-count);
            count++;
            //если записали больше 8 то выходим
            if (count==8) { count=0;   g << buf; buf=0; }
        }
    }
    cout<< endl;
    f.close();
    g.close();

    return ;
}

void dearchivingHof(){
    return ;
}
void shannonFano( int in_begin, int in_end ) {
     // not a valid parameters input
     if ( in_begin >= in_end ) {
         return;
         }

     // only 2 symbol left
     if ( in_begin == in_end - 1 ) {
         symbol.at( in_begin ).addCode( "0" );
         symbol.at( in_end ).addCode( "1" );
         return;
         }

     int highPtr = in_begin; // highPtr will go downward
     int lowPtr = in_end;
     int highSum = symbol.at( highPtr ).getFrequency();
     int lowSum = symbol.at( lowPtr ).getFrequency();

     // move the highPtr down and lowPtr up until highSum and lowSum close
     while ( highPtr != lowPtr - 1 ) {
         if ( highSum > lowSum ) {
             lowPtr --;
             lowSum += symbol.at( lowPtr ).getFrequency();
             } else {
             highPtr ++;
             highSum += symbol.at( highPtr ).getFrequency();
             }
         }

     int i;
     for ( i=in_begin; i<=highPtr; i++ ) {
         symbol.at( i ).addCode( "0" );
         }
     for ( i=lowPtr; i<=in_end; i++ ) {
         symbol.at( i ).addCode( "1" );
         }

     shannonFano( in_begin, highPtr );
     shannonFano( lowPtr, in_end );
}
void archivingSF(string path){


    //получение доступа к файлу

    path += ".txt";
    ifstream f(path, ios::in);

    map<char,int> m;


    //чтение из файла
    char c;
    int i = 0;
    while (f >> noskipws >> c) {
        if(i > 2) {
            m[c]++;
            cout << c;
        }
        i++;
    }

    int n = 0;
    for( map<char,int>::iterator itr=m.begin(); itr!=m.end(); ++itr)
    {
        n++;
        SymbolCode *p = new SymbolCode(itr->first, itr->second);
        symbol.push_back(*p);
    }
    shannonFano(0, n-1);
    //printf( "\n\n" );
    //for_each( symbol.begin(), symbol.end(), printSymbolCode );
    for(int i = 0; i < symbol.size(); i++){
        char c = symbol.at(i).getSymbol();
        string s = symbol.at(i).getCode();
        vector<bool> arr;
        for(int i1 = 0; i1 < s.length(); i1++) {
            if(s[i1] == '1'){
                arr.push_back(true);
            }
            else{
                arr.push_back(false);
            }

        }
        table[c] = arr;
    }
    ofstream g("output.haff", ios::out | ios::binary);
    //запись в файл
    int count=0; char buf=0;
    // проходимся по файлу f
    while (!f.eof())
        //берем каждый символ из f
    { char c = f.get();
        vector<bool> x = table[c];
        for(int n=0; n<x.size(); n++)
            // записываем биты в char
        {buf = buf | x[n]<<(7-count);
            count++;
            //если записали больше 8 то выходим
            if (count==8) { count=0;   g << buf; buf=0; }
        }
    }
    return ;
}

int main(int argc, char* argv[]) {

    // поучение параметров из консоли

    int i = atoi(argv[1]); // номер метода который нужно вызвать
    string path = argv[2]; // имя файла

    // выбор метода

    if(i == 1){
        archivingHof(path);
    }
    else if(i == 2){
        archivingSF(path);
    }
    else if(i == 3){

    }
    else if(i == 4){

    }

    return 0;
}
