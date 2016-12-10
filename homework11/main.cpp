#include <iostream>
#include "kmp.h"
using namespace std;

vector<int> find_pos(string substring){

    // вектор для подстрок
    vector<int> arr(substring.length(), 0);

    // заносим в 0 индекс 0
    // потому что 0 символ не может быть подстрокой самого себя
    arr[0] = 0;

    // переменная для хранения временных значений индекса подстроки
    int k = 0;

    // цикл по подстроке для предварительного анализа
    for(int i = 1; i < substring.size(); ++i){

        // если мы нашли подстроку равную префиксу и она оборволась
        // то нужно проверить возможность нахождения этого символа в другой подстроке
        // (подстроки должны пересекаться)
        // мы переходим на минимальный элемент который потонциально может стать элементом подстроки
        // потом мы еще больше ускоряем процесс и переходим на позицию в векторе по этому индексу
        // если значения совподают, то мы выходим из while-цикла
        while(k > 0 && substring[k] != substring[i]){
            k = arr[k - 1];
        }

        // если символы равны, то просто выходим из k
        if(substring[k] == substring[i]) {
            k++;
        }

        // записываем k в вектор
        arr[i] = k;
    }

    return arr;
}


vector<int> find_substrings(std::string source, std::string substring){

    // массив для всех позиций подстрок
    vector<int> all_pos;

    //cout << substring << endl;
    vector<int> arr = find_pos(substring);

    // переменная для проверки совпадений подстроки
    int k = 0;

    // цикл нахождения подстроки
    for (int i = 0; i<source.length(); ++i){

        while ((k>0) && (substring[k] != source[i]))
            k = arr[k-1];

        // если значения совпали то просто увеличиваем k
        if (substring[k] == source[i])
            k++;

        // если k == длине подстроки то обнуляем k
        if (k==substring.length()) {
            all_pos.push_back(i - substring.length() + 1);//либо продолжаем поиск следующих вхождений
            k = 0;
        }
    }

    return all_pos;
}
/*
int main() {
    vector<int> aar = find_substrings("ahahhahahahahahahhah", "ah");
    for(int i = 0; i < aar.size(); i++){
        cout << aar[i] << ' ';
    }
    return 0;
}
*/