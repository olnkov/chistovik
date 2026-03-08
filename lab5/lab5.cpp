#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Patient {
    string name;
    string surname;
    string birth;
    string oms;
    string city;
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Patient> db;

    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл\n";
        return 0;
    }

    //обработка строки

    string line;
    while (getline(file, line)) {
        int pos = line.find(';');
        string name = line.substr(0, pos);

        int pos_space = name.find(' ');
        string surname = name.substr(0, pos_space);
        string rest = line.substr(pos + 1);

        pos = rest.find(';');
        string birth = rest.substr(0, pos);
        rest = rest.substr(pos + 1);

        pos = rest.find(';');
        string oms = rest.substr(0, pos);
        rest = rest.substr(pos + 1);

        pos = rest.find(';');
        string city = rest.substr(0, pos);

    //массив

        Patient a;
        a.name = name;
        a.surname = surname;
        a.birth = birth;
        a.oms = oms;
        a.city = city;

        db.push_back(a);
    
    };

    sort(db.begin(), db.end(), [](const Patient& a, const Patient& b) {
        return a.surname < b.surname;
    });

    for (int i = 0; i < db.size() && i < 5; i++) {
        cout << db[i].surname << '\n';
    };

    //ввод ключа

    cout << "Введите фамилию для поиска\n";
    string key;
    getline(cin, key);

    //границы поиска

    int l = 0;
    int r = (int)db.size() - 1;

    int found = -1; //индекс найденной записи

    //цикл двоичного поиска
    cout << "KEY=[" << key << "]\n";
    cout << "DB0=[" << db[0].surname << "]\n";

    while (l <= r) {
        int mid = (l + r) / 2;

        if (db[mid].surname == key) {
            found = mid;
            break;
        }

        else if (db[mid].surname < key) {
            l = mid + 1;
        }

        else {
            r = mid - 1;
        }
    }

    //проверка найденных записей

    if (found == -1) {
        cout << "Запись не найдена\n";
        return 0;
    }

    int left = found;
    while (left > 0 && db[left - 1].surname == key) {
        left--;
    }

    int right = found;
    while (right + 1 < (int)db.size() && db[right + 1].surname == key) {
        right++;
    }

    //вывод

    cout << "Найдено записей: " << (right - left + 1) << '\n';
    for (int i = left; i <= right; i++) {
        cout << db[i].name << " | " << db[i].birth << " | " << db[i].oms << " | " << db[i].city << "\n";
    }

    file.close();
    return 0;
}
