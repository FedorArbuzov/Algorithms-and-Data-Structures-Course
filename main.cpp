#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <vector> // подключаем модель Векторов
#include <algorithm>
#include <math.h>
#include "char_new.cpp"
#include "char_newSF.cpp"
using namespace std;

 vector<bool> DecToBin(int number) {
    vector<bool> result(8, false);
    int i = 0;
    do
    {
        if ( (number & 1) == 0 )
            result[i] =  0;
        else
            result[i] =  1;

        number >>= 1;
        i++;
    } while ( number );

    reverse(result.begin(), result.end());
    return result;
}

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


struct MyCompare {
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

void BuildTable(Node *root) {
    if (root->left!=nullptr)
    { code.push_back(0);
        BuildTable(root->left);}

    if (root->right!=nullptr)
    { code.push_back(1);
        BuildTable(root->right);}

    if (root->left==nullptr && root->right==nullptr) table[root->c]=code;

    code.pop_back();
}

int str2int(string s) {
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
    // map для частотной таблицы
    map<char,int> m;


    //чтение из файла
    char c;
    int i = 0;
    while (f >> noskipws >> c) {
            m[c]++;
            cout << c;
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
    f.clear();
    f.seekg(0);


    // Utility variable to
    // control the size of byte
    int byte_count = 0;

    // Utility variable
    // to imitate byte
    char byte = 0;

    ofstream g("output.haff", ios::out | ios::binary);
    unsigned int table_len = table.size();
    g.write((char *) &table_len, sizeof(unsigned int));
    //запись в файл
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {
        g.write((char*) &itr->first, sizeof(char));
        cout << itr->first << ' ';
    }
    cout << endl;
    int num_of_bit = 0;
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {
        short l = itr->second.size();
        cout << l << ' ';
        num_of_bit += l;
        g.write((char *) &l, sizeof(short));
    }
    cout <<num_of_bit << endl;
    vector<bool> vec_of_bool;
    int len_for_vec = (num_of_bit / 8) + ((num_of_bit % 8) > 0 ? 1 : 0);
    vector<char> vec_of_ch(len_for_vec);
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {

        for (int i = 0; i < itr->second.size(); ++i) {
            cout<< itr->second[i];
            vec_of_bool.push_back(itr->second[i]);

        }
    }
    cout << endl;
    cout << vec_of_ch.size() << endl;
    int flag = 0;
    char tb = 0;
    vector<bool> ch(8, false);
    for(int i = 0; i < num_of_bit; i++){
        ch[flag] = vec_of_bool[i];
        flag++;
        if(flag == 8){
            for(int i1 = 0; i1 < 8; i1++){
                cout << ch[i1];
                int num = 0;
                if(ch[i1]){
                    num = 1;
                }
                else{
                    num = 0;
                }
                tb += num * pow(2, 7-i1);
            };
            cout << ' ' << tb << ' ';
            g.write((char*) &tb, sizeof(char));
            flag = 0;
            ch = vector<bool>(8, false);
            tb = 0;
        };

    }
    if(flag != 0){
        for(int i = 0; i < ch.size(); i++){
            cout << ch[i];
            int num = 0;
            if(ch[i]){
                num = 1;
            }
            else{
                num = 0;
            }
            tb += num * pow(2, 7-i);
        }
        cout << ' ' << tb << ' ';
        g.write((char*) &tb, sizeof(char));
    }
    /*
    int count = 0;
    char buf = 0;
    // проходимся по файлу f
    while (!f.eof())
        //берем каждый символ из f
    { char c = f.get();
        vector<bool> x = table[c];
        for(int n=0; n<x.size(); n++)
            // записываем биты в char
        {buf = buf | (x[n]=='1'?1:0)<<(7-count);
            count++;
            //если записали больше 8 то выходим
            if (count==8) { count=0;   g << buf; buf=0; }
        }
    }
    cout<< endl;

    // Write the
    // last byte
    if (byte_count != 0) {
        for (int i = 0; i < 8 - byte_count; ++i) {
            byte = byte | 0 << (7 - byte_count);
        }
        g.write(&byte, sizeof(char));
    }
     */
    f.close();
    g.close();

    return ;
}

void dearchivingHof(){
    ifstream f ("output.haff", ios::binary);
    unsigned int len;
    map<char, vector<bool>> m;
    f.read((char*)&len, sizeof(unsigned int));
    cout << endl;
    cout << len << endl;
    vector<char> all_ch;
    for(int i = 0; i < len; i++){
        char c;
        f.read((char*)&c, sizeof(char));
        cout << c << ' ';
        all_ch.push_back(c);

    }
    cout << endl;
    long num_of_b = 0;
    vector<short> len_of_codes;
    for(int i = 0; i < len; i++){
        short s;
        f.read((char*)&s, sizeof(short));
        len_of_codes.push_back(s);
        num_of_b += s;
        cout<< s << ' ';
    }
    cout << endl;
    int len_for_vec = (num_of_b / 8) + ((num_of_b % 8) > 0 ? 1 : 0);
    vector<char> vec_of_ch(len_for_vec);
    for(int i = 0; i < len_for_vec; i++){
         f.read((char*)&vec_of_ch[i], sizeof(char));
    }
    vector<bool> vec_all_b;
    for(int i = 0; i < len_for_vec; i++){
        cout << vec_of_ch[i] << ' ';
        int num_of_ch = +vec_of_ch[i];
        if(num_of_ch > 0){
            cout << num_of_ch << ' ';
            vector<bool> arr = DecToBin(num_of_ch);
            for(int i1 = 0; i1 < arr.size(); i1++){
                cout << arr[i1];
                vec_all_b.push_back(arr[i1]);
            }
        }
        else{
            cout << 256 + num_of_ch << ' ';
            vector<bool> arr = DecToBin(256 + num_of_ch);
            for(int i1 = 0; i1 < arr.size(); i1++){
                cout << arr[i1];
                vec_all_b.push_back(arr[i1]);
            }
        }
        cout << endl;

    }
    for(int i = 0; i < vec_all_b.size(); i++){
        cout << vec_all_b[i];
    }
    vector<vector<bool> > all_codes;
    for(int i = 0; i < len_of_codes.size(); i++){
        int code = len_of_codes[i];
        vector<bool> arr;
        for(int i1 = 0; i1 < code; i1++){
            arr.push_back(vec_all_b[0]);
            vec_all_b.erase(vec_all_b.begin());
        }
        all_codes.push_back(arr);
    }
    cout << endl;
    for(int i = 0; i < all_codes.size(); i++)
    {
        cout << all_ch[i] << ' ';
        cout << all_codes[i].size() << ' ';
        for(int i1 = 0; i1 < all_codes[i].size(); i1++){
            cout << all_codes[i][i1];
        }
        cout << endl;
    }
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
            m[c]++;
            cout << c;
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
    map<char, string> m1;


    //for_each( symbol.begin(), symbol.end(), printSymbolCode );
    for (int i = 0; i < symbol.size(); i++) {
        char c = symbol.at(i).getSymbol();
        string s = symbol.at(i).getCode();
        vector<bool> arr;
        for (int i1 = 0; i1 < s.length(); i1++) {
            if (s[i1] == '1') {
                arr.push_back(true);
            } else {
                arr.push_back(false);
            }
        }
        table[c] = arr;
    }
    f.clear();
    f.seekg(0);

    // Utility variable to
    // control the size of byte
    int byte_count = 0;

    // Utility variable
    // to imitate byte
    char byte = 0;

    ofstream g("output.shan", ios::out | ios::binary);
    char table_len = (char) table.size();
    g.write((char *) &table_len, sizeof(char));
    //запись в файл
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {
        g.write((char*) &itr->first, sizeof(char));
    }

    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {
        short l = itr->second.size();
        g.write((char *) &l, sizeof(short));
    }

    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {

        for (int i = 0; i < itr->second.size(); ++i) {

    // Write the next bit of current
    // character bin code to the byte
            byte = byte | itr->second[i] << (7 - byte_count);

    // Mark the next bit as filled
            ++byte_count;

    // Check if the byte is full
            if (byte_count == 8) {

    // Write the next byte
                g.write(&byte, sizeof(char));

    // Clear byte
                byte = 0;
                byte_count = 0;
            }
        }
    }

    // Write the
    // last byte
    if (byte_count != 0) {
        for (int i = 0; i < 8 - byte_count; ++i) {
            byte = byte | 0 << (7 - byte_count);
        }
    }
    int count = 0;
    char buf = 0;
    // проходимся по файлу f
    while (!f.eof())
        //берем каждый символ из f
    {
        char c = f.get();
        vector<bool> x = table[c];
        for (int n = 0; n < x.size(); n++)
            // записываем биты в char
        {
            buf = buf | x[n] << (7 - count);
            count++;
            //если записали больше 8 то выходим
            if (count == 8) {
                count = 0;
                g << buf;
                buf = 0;
            }
        }
    }

    return;
}


int main(int argc, char *argv[]) {

    // поучение параметров из консоли

    int i = atoi(argv[1]); // номер метода который нужно вызвать
    string path = argv[2]; // имя файла
    archivingHof(path);
    dearchivingHof();

            // выбор метода
/*
    if (i == 1) {
        archivingHof(path);
    } else if (i == 2) {
        archivingSF(path);
    } else if (i == 3) {
        dearchivingHof();
    } else if (i == 4) {

    }
*/
    return 0;
}

