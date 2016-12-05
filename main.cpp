#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <vector> // подключаем модель Векторов
#include <algorithm>
#include <math.h> // модоль для мат вычислений
#include "char_new.cpp" // класс для алг. Хоф.
#include "char_newSF.cpp" // класс для алг. Ш-Ф.
using namespace std;

// переменная для числа операций
int iterat = 0;

// перевод из 10-ной системы в 2-ную
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

// перевод из 2-ной системы в 10-ную
char VecToCh(vector<bool> arr){
    char a = 0;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i]){
            a += pow(2, 7-i);
        }
    }
    return a;
}

// Конструктор для класса Ш-Ф.
SymbolCode::SymbolCode( char in_symbol, int in_frequency ) {
    sym = in_symbol;
    freq = in_frequency;
    cd = "";
}

// Метод для получения символа из экземпляра
char SymbolCode::getSym(void) {
    return sym;
}

// Метод для получения частоты из экземпляра
int SymbolCode::getFreq(void) {
    return freq;
}

// Метод для получения кода из экземпляра
string SymbolCode::getCd(void) {
    return cd;
}

// Метод для получения кор. кода из экземпляра
void SymbolCode::addCd(string in_code) {
    cd += in_code;
}

// Структура для сравнения двух классов Хоф.
struct MyCompare {
    bool operator()
            (const Node* l, const Node* r)
    const { return l->a < r->a; }
};

// кодировка для каждого символа
vector<bool> code;

// таблица кодировок
map<char,vector<bool> > table;

// вектор символов для алгоритма Шенона-Фано
vector<SymbolCode> symbol;

// построение таблицы кодировок
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

void createCodeFile(string path, int i, bool isHaff){

    // новое имя файла
    string path_new = "";
    if(isHaff){
        path_new = path + ".haff";
    }
    else{
        path_new = path + ".shan";
    }

    // начинаем запись в файл
    ofstream g(path_new, ios::out | ios::binary);

    // записываем число уникальных символов
    unsigned int table_len = table.size();
    g.write((char *) &table_len, sizeof(unsigned int));

    // записываем число символов в начальном тексте
    g.write((char*) &i, sizeof(int));

    //запись в файл самих символов
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {
        g.write((char*) &itr->first, sizeof(char));
    }

    // запись размеров всех кодировок
    int num_of_bit = 0;
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {
        short l = itr->second.size();
        num_of_bit += l;
        g.write((char *) &l, sizeof(short));
    }

    // запись самих кодировок
    vector<bool> vec_of_bool;
    int len_for_vec = (num_of_bit / 8) + ((num_of_bit % 8) > 0 ? 1 : 0);
    vector<char> vec_of_ch(len_for_vec);
    for (map<char, vector<bool> >::iterator itr = table.begin(); itr != table.end(); ++itr) {

        for (int i = 0; i < itr->second.size(); ++i) {
            vec_of_bool.push_back(itr->second[i]);

        }
    }

    // проходимся по всей таблице кодировок и записываем ее
    int flag = 0;
    char tb = 0;
    vector<bool> ch(8, false);
    for(int i = 0; i < num_of_bit; i++){
        ch[flag] = vec_of_bool[i];
        flag++;
        if(flag == 8){
            for(int i1 = 0; i1 < 8; i1++){
                int num = 0;
                if(ch[i1]){
                    num = 1;
                }
                else{
                    num = 0;
                }
                tb += num * pow(2, 7-i1);
            };
            g.write((char*) &tb, sizeof(char));
            flag = 0;
            ch = vector<bool>(8, false);
            tb = 0;
        };

    }
    //дописываем если что-то осталось
    if(flag != 0){
        for(int i = 0; i < ch.size(); i++){
            int num = 0;
            if(ch[i]){
                num = 1;
            }
            else{
                num = 0;
            }
            tb += num * pow(2, 7-i);
        }
        g.write((char*) &tb, sizeof(char));
    }


    //записываем сам текст
    ifstream f(path+".txt", ios::out);
    int count = 0;
    vector<bool> char_new(8, false);
    while (!f.eof())
        //берем каждый символ из f
    { char c = f.get();
        vector<bool> x = table[c];
        for(int n=0; n<x.size(); n++)
            // записываем биты в char
        {
            char_new[count] = x[n];
            count++;
            if(count == 8){
                for(int i = 0; i < char_new.size(); i++){
                }
                char vrem = VecToCh(char_new);
                g.write((char*) &vrem, sizeof(char));
                count = 0;
                char_new = vector<bool>(8, false);
            }
        }
    }
    if(count != 0){
        char vrem = VecToCh(char_new);
        g.write((char*) &vrem, sizeof(char));
    }

    return ;
}

void archivingHof(string path){

    //получение доступа к файлу
    ifstream f(path + ".txt", ios::in);

    // map для частотной таблицы
    map<char,int> m;


    //чтение из файла
    char c;
    int i = 0;
    while (f >> noskipws >> c) {
            m[c]++;
           // cout << c;
        i++;
    }

    // алгоритм Хоф.
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

    createCodeFile(path, i, true);
    return ;
}

void dearchivingFile(string path){

    ifstream f (path,  ios::in);

    // получаем число уникальных символов
    unsigned int len;
    f.read((char*)&len, sizeof(unsigned int));

    // получаем число символов в тексте
    int num_of_ch;
    f.read((char*)&num_of_ch, sizeof(int));

    // получаем все уникальные символы
    vector<char> all_ch;
    for(int i = 0; i < len; i++){
        char c;
        f.read((char*)&c, sizeof(char));
        all_ch.push_back(c);

    }

    // получаем размеры кодировок
    long num_of_b = 0;
    vector<short> len_of_codes;
    for(int i = 0; i < len; i++){
        short s;
        f.read((char*)&s, sizeof(short));
        len_of_codes.push_back(s);
        num_of_b += s;
    }

    // записываем все символы, отвечающие за кодировку
    int len_for_vec = (num_of_b / 8) + ((num_of_b % 8) > 0 ? 1 : 0);
    vector<char> vec_of_ch(len_for_vec);
    for(int i = 0; i < len_for_vec; i++){
        f.read((char*)&vec_of_ch[i], sizeof(char));
    }

    // записываем все кодировки в один набор битов
    vector<bool> vec_all_b;
    for(int i = 0; i < len_for_vec; i++){
        int num_of_ch = +vec_of_ch[i];
        // перевод из char в vector<bool>
        if(num_of_ch > 0){
            vector<bool> arr = DecToBin(num_of_ch);
            for(int i1 = 0; i1 < arr.size(); i1++){
                vec_all_b.push_back(arr[i1]);
            }
        }
        else{
            vector<bool> arr = DecToBin(256 + num_of_ch);
            for(int i1 = 0; i1 < arr.size(); i1++){
                vec_all_b.push_back(arr[i1]);
            }
        }
    }

    // создаем вектор кодировок для уникальных символов
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



    // формирование пути для файла
    string path_new = "";
    if(path[path.length() - 1] == 'f'){
        path_new = path.substr(0, path.length() - 5) + "-unz-h.txt";
    }
    else{
        path_new = path.substr(0, path.length() - 5) + "-unz-s.txt";
    }

    // запись в новый файл
    ofstream out(path_new, ios::out);

    // число символов в новом файле
    int k = 0;
    // временный вектор для битов
    vector<bool> vrem;
    char tb = 0;
    bool go_out = false;
    cout << !f.eof() << ' ';
    while(!f.eof()){
        f.read((char*)&tb, sizeof(char));
        int code =int(tb);
        if(code > 0){
            vector<bool> arr = DecToBin(code);
            for(int i1 = 0; i1 < arr.size(); i1++){
                //if(go_out){break;}
                vrem.push_back(arr[i1]);
                for(int i2 = 0; i2 < all_codes.size(); i2++){
                    if(vrem == all_codes[i2]){
                        if(k < num_of_ch){out << all_ch[i2];}
                        //cout << all_ch[i2];
                        k++;
                        vrem.clear();
                        break;
                    }
                }
            }
        }
        else{
            vector<bool> arr = DecToBin(256 + code);
            for(int i1 = 0; i1 < arr.size(); i1++){
                //if(go_out){break;}
                vrem.push_back(arr[i1]);
                for(int i2 = 0; i2 < all_codes.size(); i2++){
                    if(vrem == all_codes[i2]){
                        if(k < num_of_ch){out << all_ch[i2];}
                        k++;
                        vrem.clear();
                        break;
                    }
                }
            }
        }
    }
    cout << k << ' ' << num_of_ch << endl;
    out.close();
    f.close();
    return ;
}

void dearchivingHof(string path){
    dearchivingFile(path);
    return ;
}

void dearchivingSF(string path){
    dearchivingFile(path);
    return ;
}

void shannonFano( int inBeg, int inEnd ) {

     // не валидные переменные
     if ( inBeg >= inEnd ) {
         return;
         }

     // only 2 symbol left
     if ( inBeg == inEnd - 1 ) {
         symbol.at(inBeg).addCd("0");
         symbol.at(inEnd).addCd("1");
         return;
         }

     int highPtr = inBeg; // highPtr will go downward
     int lowPtr = inEnd;
     int highSum = symbol.at(highPtr).getFreq();
     int lowSum = symbol.at(lowPtr).getFreq();

     // move the highPtr down and lowPtr up until highSum and lowSum close
     while ( highPtr != lowPtr - 1 ) {
         if ( highSum > lowSum ) {
             lowPtr --;
             lowSum += symbol.at(lowPtr).getFreq();
             } else {
             highPtr ++;
             highSum += symbol.at(highPtr).getFreq();
             }
         }

     int i;
     for ( i=inBeg; i<=highPtr; i++ ) {
         symbol.at(i).addCd("0");
         }
     for ( i=lowPtr; i<=inEnd; i++ ) {
         symbol.at(i).addCd("1");
         }

     shannonFano( inBeg, highPtr );
     shannonFano( lowPtr, inEnd );
}

void archivingSF(string path){


    //получение доступа к файлу
    ifstream f(path + ".txt", ios::in);

    map<char,int> m;


    //чтение из файла
    char c;
    int i = 0;
    while (f >> noskipws >> c) {
            m[c]++;
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

    //переносим все данные в table
    for (int i = 0; i < symbol.size(); i++) {
        char c = symbol.at(i).getSym();
        string s = symbol.at(i).getCd();
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
    f.close();
    createCodeFile(path, i, false);
    return;
}


int main(int argc, char *argv[]) {

    // поучение параметров из консоли

    int i = atoi(argv[1]); // номер метода который нужно вызвать
    string path = argv[2]; // имя файла

    // выбор метода

    if (i == 1) {
        archivingHof(path);
    } else if (i == 2) {
        dearchivingHof(path + ".haff");
    } else if (i == 3) {
        archivingSF(path);
    } else if (i == 4) {
        dearchivingSF(path + ".shan");
    }

    return 0;
}

