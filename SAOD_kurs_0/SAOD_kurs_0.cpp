#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <iterator>
#include <unordered_set>
#include <random>
using namespace std;

class SpiralHash {
private:
    vector<list<int>> table;
    int size;
    int k = 1; // Количество произведенных разбиений
    int g = 4; // Коэффициент роста 

    double log_n(double value, double n) { return log(value) / log(n); }

    int hashFunction(int key) {
        // Преобразование ключа в значение x из [0, 1)
        double A = 0.618033988749895; // Золотое сечение
        double x = key * A;
        x = x - (long)x; // Получаем дробную часть числа
        
        double c = log_n(k , g); // Вычисляем значение c = c=log g (k )
        double _x = floor(c - x) + x; // Вычисляем x' = [c - x] + x
        double i = ceil(pow(g, _x));
        return i-1;
    }

    void rehash() {
        int c = log_n(k, g); // Вычисляем значение c = c=log g (k+1)
        int start = pow(g, c); // Начальный индекс для текущей корзины
       
        int kolvo = table[k].size();
        list<int> keys = table[k];
        table[k].clear();
        k++;
        for (int key : keys)
        {      
            int index = hashFunction(key);
            table[index].push_back(key);
            kolvo--;
            if (kolvo == 0) break;
        }
        k = k;
    }

public:
    SpiralHash(int initialSize, int growthFactor) : size(0), g(growthFactor) {
        table.resize(initialSize);
    }

    void insert(int key) {
        double percent = size/ (table.size() *250.0);
        if (percent > 0.75)
        {
            table.resize(table.size() + g - 1);
            rehash();
        }

        int index = hashFunction(key);
        table[index].push_back(key);
        size++;
    }

    int search(int key) {
        int index = hashFunction(key);
        for (int k : table[index]) {
            if (k == key) {
                return index;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < table.size(); i++) {
            //for (int key : table[i]) {cout << key << " ";}
            if (table[i].size() > 0) {
                cout << "\nBucket " << i << ": "; cout << table[i].size() << endl;
            }
           // else { cout << "\nBucket " << i << ": "; cout << "." << endl; }
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    int initialSize = 3;
    int growthFactor = 4;
    SpiralHash spiralHash(initialSize, growthFactor);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 9999);


    for (int i = 0; i < 50000; ++i) {
        int randomNum = dis(gen);
        spiralHash.insert(randomNum);
    }
    spiralHash.display();

    int el;
    cout << "Введите ключ для поиска:  "; cin >> el;
    cout << "Элемент в ячейке с индексом " << spiralHash.search(el);

    return 0;
}