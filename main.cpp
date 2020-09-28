#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<math.h>

#define P 257
#define H 65537

using namespace std;

ifstream fin("words.txt");

int kol = 0;
int M, words;

struct Hash {
    int key = 0;
    char s[30] = "";
};

unsigned int fun(string s, int attempt) {
    unsigned int a{ 0 };
    for (int i = 0; i < s.size(); i++)
        a = (a + s[i] * (int)pow(P, i) * H + attempt) % M;
    return a;
}

bool search(Hash* table, int att, char* s) {
    int k = fun(s, att);
    if (strcmp(table[k].s, "") == 0) {
        cout << "Попытки : " << att << " функция вызывалась "<< att+1 <<" раз\n";
        return false;
    }
    if (strcmp(table[k].s, s) == 0) {
        cout << "Попытки : " << att << " функция вызывалась " << att + 1 << " раз\n";
        return true;
    }
    else return search(table,att+1, s);
}

bool search4check(Hash* table, int att, char* s) {
    int k = fun(s, att);
    if (strcmp(table[k].s, "") == 0) {
        return false;
    }
    if (strcmp(table[k].s, s) == 0) {
        return true;
    }
    else return search4check(table, att + 1, s);
}

int main() {
    cout << "Слолько слов внести из файла?\n";
    cin >> words;
    M = words * 2;
    Hash* table = new Hash[M];
    char exit[] = "/exit";
    char s[30];
    unsigned int k;
    int att = 0;
    clock_t start;
    clock_t finish;
    start = clock();
    for (int i = 0; i < words; i++) {
        fin >> s;
        //cout << s;
        k = fun(s, att);
        while (strcmp(table[k].s,"")) {
            kol++;
            att++;
            k = fun(s, att);
        }
        att = 0;
        strcpy(table[k].s, s);
    }
    finish = clock();
    printf("Время чтения: %.2f секунды\n\n", (double)(finish - start) / CLK_TCK);
    cout << "Последнее занесенное в таблицу слово: " << s << "\n";
    cout << kol << " коллизий \n\n";
    int p = 0;
    while (1) {
        cout << "\n=====================================\n";
        cout << "Для выхода из программы введите: /exit\n";
        cout << "Введите слово для поиска: ";
        cin >> s;
        start = clock();
        if (strcmp(exit, s) == 0)
            break;
        k = fun(s, att);
        if (search(table,0, s))
            cout << "Слово есть в списке\n";
        else
            cout << "Слова нет в списке\n";
        finish = clock();
        printf("Поиск занял %.2f sec\n\n", (double)finish - start);
    }
    return 0;
}