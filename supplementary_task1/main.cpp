#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    vector<int> x, y, u, v, a, b;
    int i, j, n;

    // подключение файлов
    ifstream ifl("input.txt");
    ofstream ofl("output.txt");

    // получение строки из файла
    string s;
    cin >> s;

    //число переправ до кажого участка на л. б.
    x.push_back(0);
    //число переправ до кажого участка на п. б.
    y.push_back(1);
    //предыдущий отрезок на л. б. до этого отрезка без притоков
    u.push_back(0);
    //предыдущий отрезок на п. б. до этого отрезка без притоков
    v.push_back(0);

    i = 1;
    for(int i = 1; i <= s.length(); i++){
        char c = s[i-1];

        x.push_back(x[i - 1]);
        y.push_back(y[i - 1]);
        u.push_back(u[i - 1]);
        v.push_back(v[i - 1]);
        if(c == 'L'){
            x[i] = x[i - 1] + 1;
            y[i] = y[i - 1];
        }
        else if(c == 'R'){
            x[i] = x[i - 1];
            y[i] = y[i - 1] + 1;
        }
        else{
            x[i] = x[i - 1] + 1;
            y[i] = y[i - 1] + 1;
        }
        if(x[i] + 1 < y[i]){
            y[i] = x[i] + 1;
        }
        if(y[i] + 1 < x[i]){
            x[i] = y[i] + 1;
        }
/*
        if(c == 'L'){
            x[i] = x[u[i - 1]] + 1;
            u[i] = i;
        }
        else if(c == 'R'){
            y[i] = y[v[i - 1]] + 1;
            v[i] = i;
        }
        else{
            x[i] = x[u[i - 1]] + 1;
            y[i] = y[v[i - 1]] + 1;
            u[i] = i;
            v[i] = i;
        }
        if(x[i - 1] == 0){
            x[i] = 1;
        }
        if(y[i - 1] == 1){
            y[i] = 2;
        }
        if(x[i] + 1 < y[i]){
            y[i] = x[i] + 1;
        }
        if(y[i] + 1 < x[i]){
            x[i] = y[i] + 1;
        }
        */
    }

    cout << y[s.length()];
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}