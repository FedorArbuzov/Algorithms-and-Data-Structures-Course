#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    //два вектора для левого и правого берегов
    vector<int> left_coast, right_coast;

    // подключение файлов
    ifstream ifl("input.txt");
    ofstream ofl("output.txt");

    // получение строки из файла
    string s;
    ifl >> s;
    ifl.close();

    //число переправ до кажого участка на л. б.
    left_coast.push_back(0);
    //число переправ до кажого участка на п. б.
    right_coast.push_back(1);


    // цикл для прохода по всему списку притоков
    for(int i = 1; i <= s.length(); i++){

        // получение конкретной переправы
        char c = s[i-1];

        // заполнение дефолтными значениями
        left_coast.push_back(left_coast[i - 1]);
        right_coast.push_back(right_coast[i - 1]);

        // если есть левый приток
        if(c == 'L'){
            left_coast[i] = left_coast[i - 1] + 1;
            right_coast[i] = right_coast[i - 1];
        }

        //  если есть правый приток
        else if(c == 'R'){
            left_coast[i] = left_coast[i - 1];
            right_coast[i] = right_coast[i - 1] + 1;
        }

        // если есть оба притока
        else{
            left_coast[i] = left_coast[i - 1] + 1;
            right_coast[i] = right_coast[i - 1] + 1;
        }

        // если на правый берег выгодно попасть из левого
        if(left_coast[i] + 1 < right_coast[i]){
            right_coast[i] = left_coast[i] + 1;
        }

        // если на левый берег выгодно попасть из правого
        if(right_coast[i] + 1 < left_coast[i]){
            left_coast[i] = right_coast[i] + 1;
        }
    }

    // вывод минимаоьного числа переправ
    ofl << right_coast[s.length()];
    ofl.close();
    return 0;
}